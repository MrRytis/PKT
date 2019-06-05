magic fibonacci(number n) {
  number a = 0
  number b = 1
  number c = 0
  number i = 2

  loop i < n {
    c = a + b
    a = b
    b = c
  
    i = i + 1
  }
  spit ""
  spit n
  spit "fibonacci number is"
  spit b
}

fibonacci(6)
