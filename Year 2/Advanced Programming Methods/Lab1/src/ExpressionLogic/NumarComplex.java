package ExpressionLogic;

public class NumarComplex {
    public NumarComplex(double re, double im) {
        this.re = re;
        this.im = im;
    }

    public double getRe() {
        return re;
    }

    public double getIm() {
        return im;
    }

    private double re;
    private double im;

    public static NumarComplex adunare(NumarComplex nr1, NumarComplex nr2) {
        return new NumarComplex(nr1.re + nr2.re, nr1.im + nr2.im);
    }

    public static NumarComplex scadere(NumarComplex nr1, NumarComplex nr2) {
        return new NumarComplex(nr1.re - nr2.re, nr1.im - nr2.im);
    }

    public static NumarComplex inmultire(NumarComplex nr1, NumarComplex nr2) {
        return new NumarComplex(nr1.re * nr2.re - nr1.im * nr2.im, nr1.re * nr2.im + nr1.im * nr2.re);
    }

    public static NumarComplex impartire(NumarComplex nr1, NumarComplex nr2) {
        return new NumarComplex((nr1.re * nr2.re - nr1.im * nr2.im) / (nr2.re * nr2.re + nr2.im * nr2.im), (nr1.re * nr2.im + nr1.im * nr2.re) / (nr2.re * nr2.re + nr2.im * nr2.im));
    }

    public static NumarComplex conjugat(NumarComplex nr) {
        return new NumarComplex(nr.re, -nr.im);
    }

    @Override
    public String toString() {
        if (im < 0)
            return Double.toString(re) + Double.toString(im) + "*i";
        else return Double.toString(re) + "+" + Double.toString(im) + "*i";
    }
}
