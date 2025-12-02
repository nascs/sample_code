// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright (c) 2025 Radxa Computer (Shenzhen) Co., Ltd.
 */

/*
 * javac -cp /usr/local/lib/java/mraa.jar:. HelloRadxaRock4D.java
 * java -cp /usr/local/lib/java/mraa.jar:. HelloRadxaRock4D
*/

import mraa.Dir;
import mraa.Gpio;
import mraa.RadxaRock4DWiring;
import mraa.mraa;
import mraa.Platform;
import mraa.Result;

public class HelloRadxaRock4D {
  static {
	try {
	  System.loadLibrary("mraajava");
	// System.load("/usr/local/lib/libmraajava.so");
	} catch (UnsatisfiedLinkError e) {
	  System.err.println(
		  "Native code library failed to load. See the chapter on Dynamic Linking Problems in the SWIG Java documentation for help.\n"
			  +
			e);
	  System.exit(1);
	}
  }

  public static void main(String argv[]) {
	Platform platform = mraa.getPlatformType();

	if (platform != Platform.RADXA_ROCK_4D) {
	  System.err.println("Error: This program can only be run on rockpi4");
	  System.exit(Result.ERROR_INVALID_PLATFORM.swigValue());
	}

	System.out.println("RadxaRock4DWiring.RADXA_ROCK_4D_PIN38.swigValue() = " + RadxaRock4DWiring.RADXA_ROCK_4D_PIN40.swigValue());
	Gpio gpio = new Gpio(RadxaRock4DWiring.RADXA_ROCK_4D_PIN38.swigValue(), false);
	gpio.dir(Dir.DIR_OUT);

	int val = gpio.read();

	int pinNumber = RadxaRock4DWiring.RADXA_ROCK_4D_PIN38.swigValue();
	System.out.println(String.format("mraa pin %d  was: %d, will set to %d\n",
		pinNumber, val, val == 0 ? 1 : 0));

	gpio.write(val == 0 ? 1 : 0);
  };
}
