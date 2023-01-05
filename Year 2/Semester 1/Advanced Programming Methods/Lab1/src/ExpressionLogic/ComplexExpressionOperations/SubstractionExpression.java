package ExpressionLogic.ComplexExpressionOperations;

import ExpressionLogic.ComplexExpression;
import ExpressionLogic.NumarComplex;
import ExpressionLogic.Operation;

public class SubstractionExpression extends ComplexExpression {
    public SubstractionExpression(Operation operation, NumarComplex[] args) {
        super(operation, args);
    }
    @Override
    public NumarComplex executeOneOperation(NumarComplex n1, NumarComplex n2){
        return NumarComplex.scadere(n1, n2);
    }
}
