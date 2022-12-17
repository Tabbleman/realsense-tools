#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <chrono>
#include <fstream>
#include <boost/format.hpp>
using namespace std;


int main(int argc, char **argv) {
    int n = 3000;
    if(argc != 2){
        cerr << "usage: recorder PATH_TO_FOLDER\n";
        
        cout << argv[1] << endl;
        
        return 1;
    }
    cout << "Start recording ......";
    char command[210], path[210];
    cv::Mat depth_frame, rgb_frame;
    cv::VideoCapture    depth(2),   rgb(4);
    string  depth_txt_full_path(argv[1]), 
            rgb_txt_full_path(argv[1]),
            depth_image_full_path,
            rgb_image_full_path;
    fstream depth_txt, rgb_txt;
    
    //create folder to save images
    
    sprintf(command, "mkdir %sdepth", argv[1]);
    sprintf(path, "%sdepth/", argv[1]);
    depth_image_full_path = path;
    system(command);
    
    
    sprintf(command, "mkdir %srgb", argv[1]);
    sprintf(path, "%srgb/", argv[1]);
    rgb_image_full_path = path;
    system(command);
    
    //save the depth file data
    depth_txt_full_path += "depth.txt";
    rgb_txt_full_path += "rgb.txt";
    //touch the file
    sprintf(command, "touch %s", depth_txt_full_path.c_str());
    sprintf(command, "touch %s", depth_txt_full_path.c_str());
    depth_txt.open(depth_txt_full_path, ios_base::out);
    rgb_txt.open(rgb_txt_full_path, ios_base::out);

    //open      depthcam    rgbcam
    
    if(!depth.isOpened() || !rgb.isOpened() || !depth_txt.is_open() || !rgb_txt.is_open()){
        cout << depth_txt_full_path << ' ' << rgb_txt_full_path << endl;
        cerr << "failed to load image or file\n";
        return 1;
    }
    
    
    
    
    while(n --){
        
         size_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
         string     depth_image_name, 
                    rgb_image_name,
                    depth_txt_info,
                    rgb_txt_info;
            
                
         depth_image_name = boost::str( boost::format("%1%%2%.png")%depth_image_full_path %now);
         rgb_image_name = boost::str( boost::format("%1%%2%.png")%rgb_image_full_path %now);
         depth_txt_info = boost::str( boost::format("%1% depth/%2%.png\n")%now %now);
         rgb_txt_info = boost::str( boost::format("%1% rgb/%2%.png\n")%now %now);
         
         depth_txt << depth_txt_info;
         rgb_txt << rgb_txt_info;
         
         
         depth >> depth_frame;
         cv::imwrite(depth_image_name, depth_frame);
         rgb >> rgb_frame;
         cv::imwrite(rgb_image_name, depth_frame);
         
         cv::waitKey(27);
        
    }
    
    
    depth_txt.close();
    rgb_txt.close();
    cout << "finish recording" << endl;
    return 0;
}
