int convergence(float x, float y, int iteration) {
  float convergence = 0;
  int i = -1;
  int result = 0;
  double xSuiv = x, ySuiv = y;
  while(convergence < 2. && i < iteration){
    double xPrec = xSuiv, yPrec = ySuiv;
    convergence = sqrt(xPrec*xPrec + yPrec*yPrec);
    xSuiv = xPrec*xPrec - yPrec*yPrec + x;
    ySuiv = 2*xPrec*yPrec + y;
    i++;
  }
  result = i%iteration;
  return result;
}

