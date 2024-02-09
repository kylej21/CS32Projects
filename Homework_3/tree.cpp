// Return the number of ways that all n2 elements of a2 appear in
  // the n1 element array a1 in the same order (though not necessarily
  // consecutively).  The empty sequence (i.e. one where n2 is 0)
  // appears in a sequence of length n1 in 1 way, even if n1 is 0.
  // For example, if a1 is the 7 element array
  //        10 50 40 20 50 40 30
  // then for this value of a2     the function must return
  //        10 20 40                        1
  //        10 40 30                        2
  //        20 10 40                        0
  //        50 40 30                        3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    return -999;  // This is incorrect.
}
  // Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}
//rearrange elements in correct order
void divide(double a[], int n, double divider,
                                    int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;

      // It will always be the case that just before evaluating the loop
      // condition:
      //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
      //  Every element earlier than position firstNotGreater is > divider
      //  Every element from position firstNotGreater to firstUnknown-1 is
      //    == divider
      //  Every element from firstUnknown to firstLess-1 is not known yet
      //  Every element at position firstLess or later is < divider

    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < divider)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > divider)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}
  // Rearrange the elements of the array so that
  // a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
  // If n <= 1, do nothing.
void order(double a[], int n)
{
    return;  // This is not always correct.
}