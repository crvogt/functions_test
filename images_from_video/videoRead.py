import cv2

#Create a VideoCapture object and read from input file
#If the input is the camera, pass 0 instead of the video file name
cap = cv2.VideoCapture('/home/carson/libs/raytrix_go_pro/raytrix_gp_experiments/Experiment3/GOPR0275.MP4')

# Check if camera opened successfully
if (cap.isOpened()== False):
  print("Error opening video stream or file")

# Read until video is completed
frameIter = 0
imgNum = 0
while(cap.isOpened()):
    # Capture frame-by-frame
    cap.set(0, frameIter)
    # cv2.waitKey(2000)
    ret, frame = cap.read()
    print(ret)
    print('frame: ' + str(frameIter))
    if ret == True:

        # Display the resulting frame

        cv2.imshow('Frame', frame)
        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

        print('frame: ' + str(frameIter))
        moveVal = raw_input('a=100, s=50, d=10, f=1, j=1, k=10, l=50, ;=100, w=save, q=quit\n')
        if moveVal == 'a':
            frameIter = frameIter - 100000
            print(frameIter)
        elif moveVal == 's':
            frameIter = frameIter - 50000
            print(frameIter)
        elif moveVal == 'd':
            frameIter = frameIter - 10000
            print(frameIter)
        elif moveVal == 'f':
            frameIter = frameIter - 1000
            print(frameIter)
        elif moveVal == 'j':
            frameIter = frameIter + 1000
            print(frameIter)
        elif moveVal == 'k':
            frameIter = frameIter + 10000
            print(frameIter)
        elif moveVal == 'l':
            frameIter = frameIter + 50000
            print(frameIter)
        elif moveVal == ';':
            frameIter = frameIter + 100000
            print(frameIter)
        elif moveVal == 'w':
            print('saving image...')
            saveTo = '/home/carson/libs/raytrix_go_pro/raytrix_gp_experiments/Experiment3/goproImages/' + str(imgNum) + '.png'
            cv2.imwrite(saveTo,frame)
            imgNum = imgNum + 1
        elif moveVal == 'q':
            print('breaking...')
            break

        #print('here')
        #cv2.destroyAllWindows()

# When everything done, release the video capture object
cap.release()

# Closes all the frames
cv2.destroyAllWindows()
