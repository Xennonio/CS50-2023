DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS transactions;
DROP TABLE IF EXISTS portfolio;

CREATE TABLE users (id INTEGER, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00, PRIMARY KEY(id));
CREATE TABLE transactions (id INTEGER, shares INTEGER NOT NULL, symbol TEXT NOT NULL, price INTEGER NOT NULL, transacted TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP);
CREATE TABLE portfolio (id INTEGER, shares INTEGER NOT NULL, symbol TEXT NOT NULL);