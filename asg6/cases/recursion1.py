def f():
  x=9
  def g(x):
    if x == 0:
      return 1
    else:
      return g(x-1)+x
  print g(5)

print f()
     
