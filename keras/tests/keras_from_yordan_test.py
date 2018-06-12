input_img = Input(shape=(100, 100, 3))  # adapt this if using channels_first image data format
		x = Conv2D(16, (3, 3), activation='relu', padding='same')(input_img) # (100, 100)
		x = MaxPooling2D((2, 2), padding='same')(x) # (50, 50)
		x = Conv2D(8, (3, 3), activation='relu', padding='same')(x) # (50, 50)
		x = MaxPooling2D((2, 2), padding='same')(x) # (25, 25)
		x = Conv2D(8, (4, 4), activation='relu')(x) # (22, 22)
		x = MaxPooling2D((2, 2), padding='same')(x) # (11, 11)
		x = Conv2D(8, (4, 4), activation='relu')(x) # (8, 8)
		reshaped_encoded = Flatten()(x)

		latent = Dense(8)(reshaped_encoded) # (1,8)

		upsampled_decoded = Dense(8 * 8)(latent) # (1,64)
		reshaped_decoded = Reshape([8, 8, 1])(upsampled_decoded) # (8,8)
		x = Conv2D(8, (3, 3), activation='relu', padding='same')(reshaped_decoded) # (8, 😎
		x = UpSampling2D((2, 2))(x) # (16, 16)
		x = Conv2D(16, (3, 3), activation='relu')(x) # (14, 14)
		x = UpSampling2D((2, 2))(x) # (28, 28)
		x = Conv2D(16, (4, 4), activation='relu')(x) # (25, 25)
		x = UpSampling2D((2, 2))(x) # (50, 50)
		x = Conv2D(16, (3, 3), activation='relu', padding='same')(x) # (50, 50)
		x = UpSampling2D((2, 2))(x) # (100, 100)
		output_img = Conv2D(3, (3, 3), activation='sigmoid', padding='same')(x) # (100, 100)