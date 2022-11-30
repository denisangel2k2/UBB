module com.socialnetwork.socialnetwork {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens com.socialnetwork.app to javafx.fxml;
    exports com.socialnetwork.app;
    exports com.socialnetwork.app.controllers;
    opens com.socialnetwork.app.controllers to javafx.fxml;
}