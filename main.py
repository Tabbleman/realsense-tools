import pyrealsense2 as rs
import numpy as np
import cv2
from datetime import datetime
pipeline = rs.pipeline()
config = rs.config()
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

pipeline.start(config)
def timestamp():
    dt = datetime.now()
    ts = datetime.timestamp(dt)

    return str(round(ts,6))
def main(fullpath):
    """
    :param fullpath:the absolute path folder you want to save your data [end with '/']
    :return nothing:
    """
    # fullpath = "/home/cheems/dataset/2022-12-14/"
    depthfile = open(str(fullpath + "depth.txt"), "w")
    rgbfile = open(str(fullpath + "rgb.txt"), "w")

    try:

        while True:
            frames = pipeline.wait_for_frames()
            depth_frame = frames.get_depth_frame()
            color_frame = frames.get_color_frame()
            if not depth_frame or not color_frame:
                continue

            # convert images to numpy arrays
            depth_image = np.asanyarray(depth_frame.get_data())
            color_image = np.asanyarray(color_frame.get_data())
            ts = timestamp();
            depthfile.write(str(ts + " depth/" + ts + ".png\n"))
            rgbfile.write(str(ts + " rgb/" + ts + ".png\n"))

            cv2.imwrite(str(fullpath + "rgb/" + ts + ".png"), color_image)
            cv2.imwrite(str(fullpath + "depth/" + ts + ".png"), depth_image)

            cv2.imshow("dp", depth_image)
            cv2.imshow("rgb", color_image)
            print("image saved")
            if cv2.waitKey(1) == ord("q"):
                break
    except :
        pass

if __name__ == '__main__':

    main("")
