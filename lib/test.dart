import 'dart:async';

import 'package:dart_ping/dart_ping.dart';
import 'package:flutter/services.dart';

class Test {
  static const MethodChannel channel = const MethodChannel('test');

  late String cameraip;
  late String cameraurl;
  late String imagename;
  Test(String cameraip, String cameraurl, String imagename) {
    this.cameraip = cameraip;
    this.cameraurl = cameraurl;
    this.imagename = imagename;
  }
  String status = "";
  func(PingData event) async {
    print(event.response);

    if (event.response != null) {
      String x = await channel.invokeMethod(
          'getPlatformVersion', {"url": cameraurl, "fname": imagename});
      status = "done";
      return status;
      //print("cpp debug " + x);
    } else {
      //throw ("Camera is not connected");
      status = "error";
      return status;
    }
  }

  Stream<PingData> checkping() {
    final ping = Ping(cameraip, count: 5);

    // Begin ping process and listen for output
    return ping.stream;
  }

  MethodChannel getFrames() {
    return channel;
  }

  // static Future<String?> get platformVersion async {
  //   final String? version = await channel.invokeMethod('getPlatformVersion');

  //   print(version);
  //   return version;
  // }
}
