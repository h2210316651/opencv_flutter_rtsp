import 'dart:async';

import 'package:flutter/services.dart';

class Test {
  static const MethodChannel _channel = const MethodChannel('test');
  final String camera1 =
      "rtsp://admin:kkk2019@192.168.0.156/cam/realmonitor?channel=1&subtype=0";
  getFrames() async {
    String status = "";
    try {
      String x =
          await _channel.invokeMethod('getPlatformVersion', {"url": camera1});
      status = "done";
      print("cpp debug " + x);
    } on PlatformException catch (e) {
      status = "error";

      print(e);
    }
    print("done");
    return status;
  }

  // static Future<String?> get platformVersion async {
  //   final String? version = await _channel.invokeMethod('getPlatformVersion');

  //   print(version);
  //   return version;
  // }
}
