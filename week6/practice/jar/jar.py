class Jar:
  def __init__(self, capacity):
    if capacity < 0:
      raise ValueError("Not an non-negative Integer")
    self.size = 0
    self._capacity = capacity

  def __str__(self):
    return '🍪' * self.size

  def deposit(self, n):
    self.size += n
    if self.size > self._capacity:
      raise ValueError("Beyond Capacity")

  def withdraw(self, n):
    self.size -= n
    if self.size < 0:
      raise ValueError("There isn't that amount in the jar")

  @property
  def capacity(self):
    return self._capacity

  @property
  def size(self):
    return self._size

  @size.setter
  def size(self, n):
    self._size = n

def main():
  jar = Jar(20)
  print(str(jar.capacity))
  jar.deposit(20)
  print(str(jar))
  jar.withdraw(17)
  print(jar.size)
  print(str(jar))

main()