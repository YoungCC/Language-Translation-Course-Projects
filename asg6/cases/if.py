x=9
def f():
  x = 0
  if x == 0: 
    print 99
    x = 17
    if x > 0: 
      print 1
      return x*x/2
    if x < 0: 
      print 2
      return x%x**2
    print x

f()
print 17
print x
