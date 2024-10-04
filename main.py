import cv2

camera = cv2.VideoCapture(0)

return_value, image = camera.read()
cv2.imwrite('opencv0'+'.png', image)

from tensorflow.keras.models import load_model
loaded_model = load_model('plant_disease_trained.h5')

from PIL import Image
import numpy as np
img = Image.open("opencv0.png")
img = img.resize((512, 512))
img_array = np.array(img) / 255.0
img_array = np.expand_dims(img_array, axis=0)  # Adding a batch dimension

predictions = loaded_model.predict(img_array)

classes = ['healthy', 'multiple_diseases', 'rust', 'scab']
print(classes[np.argmax(predictions)])