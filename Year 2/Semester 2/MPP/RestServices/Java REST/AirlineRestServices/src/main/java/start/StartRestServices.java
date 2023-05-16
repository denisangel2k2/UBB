package start;

import airline.persistence.FlightRepository;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Primary;

import java.io.IOException;
import java.util.Properties;


@ComponentScan({"start","airline.persistence","airline","rest"})
@SpringBootApplication
public class StartRestServices {
    public static void main(String[] args) {
        SpringApplication.run(StartRestServices.class, args);
    }

    @Bean(name="props")
    @Primary
    public Properties dbProperties() {
        Properties serverProps=new Properties();
        try {
            serverProps.load(StartRestServices.class.getResourceAsStream("/bd.config"));
            System.out.println("Server properties set. ");
            serverProps.list(System.out);
        } catch (IOException e) {
            System.err.println("Cannot find chatserver.properties "+e);
        }
        return serverProps;
    }
}
