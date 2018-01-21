x=3
y=-6
def f(x, y):
  z=x*y-x/y
  w=x
  v=x+z 
  print z
  print w
  print v
  def g(x,y,z):
    print x+y-z
    w=x**y-z//2
    return w
  g(2,3,5)

f(2,8)
f(-1,6)
