module com.socialnetwork.socialnetwork {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;

    opens com.socialnetwork.socialnetwork to javafx.fxml;
    exports com.socialnetwork.socialnetwork;
}