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
