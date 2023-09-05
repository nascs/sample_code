/*
 * Author: Brendan Le Foll <brendan.le.foll@intel.com>
 * Author: Petre Eftime <petre.p.eftime@intel.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * SPDX-License-Identifier: MIT
 */

//! [Interesting]
import mraa.Dir;
import mraa.Gpio;
import mraa.RockPi4;
import mraa.mraa;
import mraa.Platform;
import mraa.Result;

public class HelloRockpi4 {
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

	if (platform != Platform.ROCKPI4) {
	  System.err.println("Error: This program can only be run on rockpi4");
	  System.exit(Result.ERROR_INVALID_PLATFORM.swigValue());
	}

	System.out.println("RockPi4.ROCKPI4_GPIO71.swigValue() = " + RockPi4.ROCKPI4_GPIO71.swigValue());
	Gpio gpio = new Gpio(RockPi4.ROCKPI4_GPIO71.swigValue(), false);
	gpio.dir(Dir.DIR_OUT);

	int val = gpio.read();

	System.out.println(String.format("GPIO%d (mraa pin %d) was: %d, will set to %d\n", 182,
		gpio.getPin(), val, val == 0 ? 1 : 0));

	gpio.write(val == 0 ? 1 : 0);
  };
}
// ! [Interesting]
