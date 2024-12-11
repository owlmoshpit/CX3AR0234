


import av
import cv2
import numpy as np

# Open the camera using PyAV
container = av.open("video=CX3-UVC", format="dshow", options={"video_size": "1920x1080", "pix_fmt": "gray"})

# Decode frames
for frame in container.decode(video=0):
    # Convert PyAV frame to a NumPy array
    img = frame.to_ndarray(format="gray")

    # Display the frame using OpenCV
    cv2.imshow("Frame", img)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
