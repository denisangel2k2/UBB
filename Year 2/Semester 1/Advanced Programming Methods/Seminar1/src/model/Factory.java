package model;

import container.Container;
import container.Strategy;

import java.util.HashMap;

public interface Factory {


    Container createContainer(Strategy strategy);
}

