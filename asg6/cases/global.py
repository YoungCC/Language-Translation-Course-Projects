x=-2
y=3;
def f():
  x=1
  y=9
  def g():
    global x,y
    w = x+y
    z = x+y-x/y+x**y
    print w
    print z
  g()
  print x+y

f()
f()

  
