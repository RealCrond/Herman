import numpy as np
import cv2
from matplotlib import pyplot as plt

img_gray = cv2.imread('data/lena.jpg', 0)

img_float32 = np.float32(img_gray)

dft = cv2.dft(img_float32, flags= cv2.DFT_COMPLEX_OUTPUT)
dft_shift = np.fft.fftshift(dft)
# 得到灰度图能表示的形式
#print(dft_shift.shape)
#magnitude_spectrum = 20*np.log(cv2.magnitude(dft_shift[:, :, 0], dft_shift[:, :, 1]))
#print(magnitude_spectrum.shape)

mask = np.zeros((img_gray.shape[0], img_gray.shape[1], 2), np.uint8)
row, col = int(img_gray.shape[0]/2), int(img_gray.shape[1]/2)
mask[row-30:row+30, col-30:col+30] = 1

mask_img = dft_shift*mask

img_idft = np.fft.ifftshift(mask_img)

img_idft = cv2.idft(img_idft)

img_idft = cv2.magnitude(img_idft[:, :, 0], img_idft[:, :, 1])

plt.subplot(121), plt.imshow(img_idft,cmap="gray")
plt.title("111"), plt.xticks([]), plt.yticks([])
plt.show()


'''
plt.subplot(131), plt.imshow(img_gray, cmap = 'gray')
plt.title('Input Image'), plt.xticks([]), plt.yticks([])
plt.subplot(132), plt.imshow(magnitude_spectrum, cmap = 'gray')
plt.title('Magnitude Spectrum'), plt.xticks([]), plt.yticks([])
plt.subplot(133), plt.imshow(img_idft, cmap = 'gray')
plt.title('Magnitude Spectrum1'), plt.xticks([]), plt.yticks([])
plt.show()
'''