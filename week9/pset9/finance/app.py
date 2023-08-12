import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, not_int

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # display HTML table with
        # all stocks owned
        # number of shares of each stock
        # current price of each stock
        # total value of each holding
        # display user's current cash balance
        # display total value of stocks and cash together
    rows = db.execute("SELECT symbol FROM portfolio WHERE id = ? AND shares != 0", session["user_id"])

    try:
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    except:
        return render_template("login.html")

    symbols = []

    total = cash

    for item in rows:
        symbols.append(lookup(item["symbol"]))

    for symbol in symbols:
        symbol["shares"] = db.execute("SELECT shares AS quantity FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], symbol["symbol"])[0]['quantity']
        symbol["total"] = symbol["shares"]*symbol["price"]
        symbol["price"] = usd(symbol["price"])
        total += symbol["total"]
        symbol["total"] = usd(symbol["total"])

    return render_template("portfolio.html", symbols = symbols, cash = usd(cash), total = usd(total))


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """Add Cash"""
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    if request.method == "POST":
        if not request.form.get("cash_added"):
            return apology("enter a value", 400)
        else:
            cash_added = float(request.form.get("cash_added"))
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + cash_added, session["user_id"])

            return redirect("/")
    else:
        return render_template("cash.html", cash = usd(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # if POST: purchase the stock so long as the user can afford it
        # ask for symbol and number of shares
        # check for valid input
        # decide on table name(s) and fields
        # use CREATE TABLE to add new table to db (using appropriate SQL types)
        # ensure user has enough cash to afford the stock, otherwise return an apology
        # run SQL statement in db to purchase stock
        # update cash to reflect purchased stock
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        if not request.form.get("shares"):
            return apology("missing shares", 400)

        symbol_lookup = lookup(request.form.get("symbol"))

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        shares = request.form.get("shares")

        if symbol_lookup is None:
            return apology("invalid symbol", 400)

        if not_int(shares):
            return apology("invalidy shares", 400)

        shares = int(shares)

        old_shares = db.execute("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], request.form.get("symbol").upper())

        if not old_shares:
            old_shares = 0
        else:
            old_shares = old_shares[0]["shares"]

        if shares <= 0:
            return apology("invalidy shares", 400)

        if symbol_lookup["price"]*shares > cash:
            return apology("can't afford", 400)

        else:
            db.execute("INSERT INTO transactions (id, shares, symbol, price) VALUES (?, ?, ?, ?)", session["user_id"], shares, request.form.get("symbol").upper(), usd(symbol_lookup["price"]))
            symbol_portfolio = db.execute("SELECT symbol FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], request.form.get("symbol").upper())
            if not symbol_portfolio:
                db.execute("INSERT INTO portfolio (id, shares, symbol) VALUES (?, ?, ?)", session["user_id"], shares, request.form.get("symbol").upper())
            else:
                db.execute("UPDATE portfolio SET shares = ? WHERE id = ? AND symbol = ?", old_shares + shares, session["user_id"], request.form.get("symbol").upper())

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - symbol_lookup["price"]*shares, session["user_id"])

        return redirect("/")

    # if GET: display form to buy a stock
    else:
        return render_template("buy.html")

# 6
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # display a table with a history of all transactions, with one row for every buy and sell
    # implementation depends on how your db is structured
    transactions = db.execute("SELECT * FROM transactions WHERE id = ?", session["user_id"])

    return render_template("history.html", transactions = transactions)

    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # if POST: lookup the stock symbol with lookup function, and display the result
        # lookup takes a stock symbol and return a stock quote
        # if lookup is successful, it returns a dictionary with name, price, symbol
        # if lookup is unscessful, function returns None
    if request.method == "POST":
        symbol_lookup = lookup(request.form.get("symbol"))
        if symbol_lookup is None:
            return apology("invalid symbol", 400)
        else:
            return render_template("quoted.html", symbol_lookup = symbol_lookup, price = usd(symbol_lookup["price"]))

    # if GET: display form to request a stock quote
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # if POST: check for possible errors and insert the new user into users table
        # return apology if: some field is blank, password confirmation don't match, username already taken
        # db shouldn't store text passwords, use generate_password_hash to generate a hash of the password
        # use db.execute and ? as placeholder to inster the new user into users table
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't mach", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 0:
            return apology("username is not available", 400)

        password_hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), password_hash)

        # Log user in
            # session["user_id"] keeps track of which user is logged in
        session["user_id"] = db.execute("SELECT id FROM users WHERE username = ?", request.form.get("username"))[0]["id"]

        return redirect("/")

    # if GET: display registration form
        # register.html (choose: username, password, verify password again)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # if POST: check for errors and sell the specified number of shares of stock, updating user's cash
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        if not request.form.get("shares"):
            return apology("missing shares", 400)

        symbol_lookup = lookup(request.form.get("symbol"))

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        shares = request.form.get("shares")

        if not_int(shares):
            return apology("invalidy shares", 400)

        shares = int(shares)

        quantity = db.execute("SELECT shares AS quantity FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], symbol_lookup["symbol"])[0]["quantity"]

        if shares <= 0:
            return apology("invalidy shares", 400)

        if shares > quantity:
            return apology("too many shares", 400)

        else:
            db.execute("INSERT INTO transactions (id, shares, symbol, price) VALUES (?, ?, ?, ?)", session["user_id"], -shares, request.form.get("symbol"), usd(symbol_lookup["price"]))
            db.execute("UPDATE portfolio SET shares = ? WHERE id = ? AND symbol = ?", quantity - shares, session["user_id"], symbol_lookup["symbol"])

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + symbol_lookup["price"]*shares, session["user_id"])

        return redirect("/")

    # if GET: display form to sell a stock
    else:
        symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE id = ?", session["user_id"])
        return render_template("sell.html", symbols = symbols)

# 7 - personal touch
# allow users to change password, add cash, ...
# https://iexcloud.io/markets/
# https://finance.cs50.net/