#include "include/test/test_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>
#include<iostream>
#include<opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <map>
#include <memory>
#include <sstream>

namespace {

class TestPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  TestPlugin();

  virtual ~TestPlugin();

 private:
  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

// static
void TestPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "test",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<TestPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

TestPlugin::TestPlugin() {}

TestPlugin::~TestPlugin() {}

void TestPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
      if (method_call.method_name().compare("getFrame") == 0) {
        
        // try{
          
          
          
        //   cap>>frame;
        //   if (frame.empty())
        //     {
        //       std::cout<<"error grabbing fame"<<std::endl;
        //     }
        //   else{
        //      cv::imwrite("C:\\Users\\Srinath\\Desktop\\test.jpeg",frame);
        //   }
         
        // }catch(std::string e){
        //   std::cout<<"error grabbing fame"<<std::endl;
        // }
        
      }
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    std::string url;
    const auto* arguments = std::get_if< flutter::EncodableMap>(method_call.arguments());
    if (arguments) {
    auto url_it = arguments->find(flutter::EncodableValue("url"));
    if (url_it != arguments->end()) {
      url = std::get<std::string>(url_it->second);
      std::cout<<url<<std::endl;
    }
  }
    try{
          
          
          cv::VideoCapture cap(url);
          cv::Mat frame;
          if(cap.isOpened()==true){
            cap>>frame;
            cap.release();
          if (frame.empty())
            {
              std::cout<<"error grabbing fame"<<std::endl;
            }
          else{
             cv::imwrite("C:\\Users\\Srinath\\Desktop\\test.jpeg",frame);
          }
          }
          else{
            throw "camera disxonnected";
            
          }
          
         
        }catch(std::string e){
          // std::cout<<"error grabbing fame"<<std::endl;
          // std::cout<<x<<std::endl;
          version_stream<<e;
        }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } else {
    result->NotImplemented();
  }
}

}  // namespace

void TestPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  TestPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
