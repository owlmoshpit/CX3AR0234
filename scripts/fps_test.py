import av
import time

# Open the camera using PyAV
container = av.open("video=CX3-UVC", format="dshow", options={"video_size": "1920x1080", "pix_fmt": "gray"})

frame_count = 0
start_time = time.time()

# Decode frames
for frame in container.decode(video=0):
    frame_count += 1

    # Measure FPS every 100 frames
    if frame_count % 100 == 0:
        elapsed_time = time.time() - start_time
        fps = frame_count / elapsed_time
        print(f"Frames processed: {frame_count}, FPS: {fps:.2f}")

    # Optional: Limit to a specific number of frames for testing
    if frame_count == 400:
        break