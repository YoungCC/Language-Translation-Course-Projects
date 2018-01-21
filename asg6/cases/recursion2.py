def f(x):
  if x == 0:
    return 1
  else:
    return f(x-1)*x

def g(y):
  if y == 0:
    return 2
  print f(9)
  return g(y-1)+y
print g(5)


def h():
  print f(7)

h()


