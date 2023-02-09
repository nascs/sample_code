import mraa.Dir;
import mraa.Gpio;
import mraa.Result;
import mraa.mraa;

public class Blink {
    static {
        try {
            System.loadLibrary("mraajava");
        } catch (UnsatisfiedLinkError e) {
            System.err.println(
                    "Native code library failed to load. See the chapter on Dynamic Linking Problems in the SWIG Java documentation for help.\n"
                            +
                            e);
            System.exit(1);
        }
    }

    public static void main(String argv[]) throws InterruptedException {
        int pin = 3;
        Gpio gpio = new Gpio(pin);
        Result result = gpio.dir(Dir.DIR_OUT);

        if(result != Result.SUCCESS) {
            mraa.printError(result);
            System.exit(1);
        }
        for (int i = 100; i > 0; --i) {
            gpio.write(1);
            Thread.sleep(1000);
            gpio.write(0);
            Thread.sleep(1000);
        }
    }
}