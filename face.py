# import cv2
import face_recognition

# Load an image
image = cv2.imread('path/to/your/image.jpg')

# Convert the image from BGR to RGB
rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

# Find all face locations in the image
face_locations = face_recognition.face_locations(rgb_image)

# Draw rectangles around the faces
for face_location in face_locations:
    top, right, bottom, left = face_location
    cv2.rectangle(image, (left, top), (right, bottom), (0, 255, 0), 2)

# Display the result
cv2.imshow('Face Detection', image)
cv2.waitKey(0)
cv2.destroyAllWindows()
