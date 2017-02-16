typedef complex<double> base;

void fft (vector<base> & a, bool invert) {
	int n = (int) a.size();
	if (n == 1)  return;

    vector<base> a0 (n/2), a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i+1];
	}
    fft (a0, invert);
    fft (a1, invert);

	double ang = 2*PI/n * (invert ? -1 : 1);
    base w (1), wn (cos(ang), sin(ang));
	for (int i=0; i<n/2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
		if (invert)
            a[i] /= 2, a[i+n/2] /= 2;
        w *= wn;
	}
}


/*
1. Build two different vectors with coefficient of the equation ( 3 + x + 2x^2 will be [3,1,2] )
2. Send them to multiply ( arr, brr, res )
3. res vector contains result of multiplication.

WARNING: FFT causes precision error. multiply() rounds them to integer.
*/

void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
    vector<base> fa (a.begin(), a.end()), fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize (n), fb.resize (n);

    fft (fa, false), fft (fb, false);
	for (size_t i=0; i<n; ++i)
        fa[i] *= fb[i];
    fft (fa, true);

    res.resize (n);
	for (size_t i=0; i<n; ++i)
        res[i] = int (fa[i].real() + 0.5);
}

