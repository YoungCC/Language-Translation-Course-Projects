x=1

def f():
  x=6
  print x

def g():
  x=9
  def h():
    print x
    f()
  print x
  h()

print x
g()
g()
