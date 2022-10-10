package ExpressionLogic;

public abstract class ComplexExpression {
    private Operation operation;
    private NumarComplex[] args;
    public ComplexExpression(Operation operation, NumarComplex[] args) {
        this.operation = operation;
        this.args = args;
    }

    public abstract NumarComplex executeOneOperation(NumarComplex n1, NumarComplex n2);

    public final NumarComplex execute() {
        NumarComplex rezultat = new NumarComplex(args[0].getRe(), args[0].getIm());
        for (int i = 1; i < args.length; i++)
            rezultat = executeOneOperation(rezultat, args[i]);
        return rezultat;
    }


}
