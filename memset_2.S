.global memset_2

// a0: ptr
// a1: c
// a2: n
memset_2:
  // t0 <- word
  mv  t0, a1
  sll t0, t0, 8
  add t0, t0, a1
  mv  t1, t0
  sll t0, t0, 16
  add t0, t0, t1

  // t2 <- addr (a0 is return value)
  mv t2, a0

  // t1 <- 4
  add t1, x0, 4

  // if (n < 4) go last
  blt a2, t1, last

// sw loop
loop:
  sw    t0, 0(t2)
  add   t2, t2, 4
  add   a2, a2, -4
  bge   a2, t1, loop // if (n >= 4) go loop

last:
  beqz  a2, end
  sb    t0, 0(t2)
  add   a2, a2, -1
  add   t2, t2, 1
  bnez  a2, last

end:
  ret