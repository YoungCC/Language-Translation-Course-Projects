def d(n):
  try:
    print "Try" 
    count = 0
    for x in range(8):
      if x < 8:
        print x
      else:
        print x+1
      for y in range(9): 
        count += y
    for z in range(6):
      if z < 5:
        print z + count
  except:
    x = 9;
    y = 1;
    while x > n:
      print x
    else:
      pass
    while y < n:
      print "Opps"
  except:
    print "bad guy"
  finally:
    print "good boy"

def f():
  D = {'jack':100, 'rose':101}
  for x in range(3):
    print "hello"
  try:  
    print D[x]
  except:
    print "bad key"
  except:
    print ""
  for x in range(3):
      print x

class MyPython:
  def h():
    for x in range(5):
      if x < 3:
        print x
      else:
        print x+1
  def m():  
    pass  
    def s():  
      print "" 
 
class Parent:
    def _init_(self):
        self.name = "parent"
    def getName(self):
        print self.name
    class Child:
        def _init_(self):
            self.name = 'child'
        def getName(self):
            print self.name
        class Grandchild:
            def _init_(self):
                self.name = 'grandchild'
            def getName(self):
                print self.name  
        def x():
            pass
    def y():
        pass

if 1:
  print "if"

while 1:
  print "while"

for x in range(3): 
  pass

try:
  print ""
except:
  pass
   
if _name_ == "main":
    Child = Parent.Child()
    Child.getName()


d(3)
f()

