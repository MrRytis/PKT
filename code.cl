func fibonacci(int n) {
  int a = 0
  int b = 1
  int c = 0
  int i = 2

  while i <= n {
    c = a + b
    a = b
    b = c
  
    i = i + 1
  }

  print n
  print "fibonacci number is"
  print b
}

fibonacci(15)
