def generate_conv_stft_examples(corpus, output_gen, batch_size=50,
                                do_log=False, do_mag=False, do_pobs=False,
                                do_mfcc=False):
    TIMESTEPS = 100
    batch_x = []
    batch_y1 = []
    batch_y2 = []
    batch_count = 0

    while True:
        mix, s_1_pad, s_2_pad = create_mixture(corpus)
        if not do_mfcc:
            Mix_STFT, s_1_STFT, s_2_STFT = do_STFT_on_data(mix,
                                                           s_1_pad, s_2_pad,
                                                           do_log=do_log,
                                                           do_mag=do_mag)
        else:
            Mix_STFT, speaker_1_STFT, speaker_2_STFT = get_MFCC(mix,
                                                                s_1_pad,
                                                                s_2_pad)
        # Generating sequences
        i = 0
        while i + TIMESTEPS < len(Mix_STFT):
            batch_x.append(Mix_STFT.reshape(Mix_STFT.shape[0],
                                            Mix_STFT.shape[1], 1))
            batch_y1.append(s_1_STFT.reshape(Mix_STFT.shape[0],
                                             Mix_STFT.shape[1], 1))
            batch_y2.append(s_2_STFT.reshape(Mix_STFT.shape[0],
                                             Mix_STFT.shape[1], 1))
            i += TIMESTEPS // 2

            batch_count = batch_count + 1

            if batch_count == batch_size:
                inp = np.array(batch_x).reshape((batch_size,
                                                 Mix_STFT.shape[0],
                                                 Mix_STFT.shape[1], 1))
                out1 = np.array(batch_y1).reshape((batch_size,
                                                   Mix_STFT.shape[0],
                                                   Mix_STFT.shape[1], 1))
                out2 = np.array(batch_y2).reshape((batch_size,
                                                   Mix_STFT.shape[0],
                                                   Mix_STFT.shape[1], 1))
                yield({'input': inp},
                      {'speaker_1': out1, 'speaker_2': out2})
                batch_x = []
                batch_y1 = []
                batch_y2 = []
                batch_count = 0

if __name__ == "__main__":
    import corpus
    # x, y = next(generate_stft_examples(corpus.experiment_files_voc,
    #                                    create_clust_output, batch_size=50))
    # print(x['input'].shape)
    # print(y['kmeans_o'].shape)

    # x, y = next(generate_stft_examples(corpus.experiment_files_voc,
    #                                    create_stft_output, batch_size=50))
    # print(x['input'].shape)
    # print(y['speaker_1'].shape)

    x, y = next(generate_conv_stft_examples(corpus.experiment_files_voc_sample,
                                            create_stft_output, batch_size=50))
    print(x['input'].shape)
    print(y['speaker_1'].shape)