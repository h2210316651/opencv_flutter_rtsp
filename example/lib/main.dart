import 'package:flutter/material.dart';
import 'dart:async';

import 'package:test/test.dart';
import 'package:dart_ping/dart_ping.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _platformVersion = 'Unknown';

  @override
  void initState() {
    super.initState();
    initPlatformState();
  }

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    String platformVersion = "";
    // Platform messages may fail, so we use a try/catch PlatformException.
    // We also handle the message potentially returning null.

    // If the widget was removed from the tree while the asynchronous platform
    // message was in flight, we want to discard the reply rather than calling
    // setState to update our non-existent appearance.
    if (!mounted) return;

    setState(() {
      _platformVersion = platformVersion;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: Column(
            children: [
              RaisedButton(
                onPressed: () async {
                  Test a = new Test(
                      "192.168.0.155",
                      "rtsp://admin:kkk2019@192.168.0.155/cam/realmonitor?channel=1&subtype=0",
                      "C:\\Users\\Srinath\\Desktop\\test.jpeg");
                  a.checkping().listen((event) async {
                    print(event.summary?.received);
                    if (event.summary?.received != 0 && event.summary != null) {
                      await a.getFrames().invokeMethod('getPlatformVersion',
                          {"url": a.cameraurl, "fname": a.imagename});
                    } else {
                      print("error initialising camera");
                    }
                  });
                },
                child: Text("take picture"),
              ),
              Text("Status :"),
              Text(_platformVersion),
            ],
          ),
        ),
      ),
    );
  }
}
