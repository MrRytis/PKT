magic fibonacci(number n) {
  fibRec(0, 1, 1, n)
}

magic fibRec(number a, number b, number counter, number len) {
  maybe counter < len {
    counter = counter + 1
    fibRec(b, a + b, counter, len)
  }
  else {
    spit b
  }
}



fibonacci(5)
