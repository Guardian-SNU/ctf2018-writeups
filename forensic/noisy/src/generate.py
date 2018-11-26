import qrcode
import numpy as np
import random
import imageio


def gen_qr(data, version=1, box_size=1, correction=qrcode.constants.ERROR_CORRECT_H, border=0):
    qr = qrcode.QRCode(
        version=version,
        error_correction=correction,
        box_size=box_size,
        border=border
    )
    qr.add_data(data)
    qr.make(fit=True)

    img = qr.make_image(fill_color='black', back_color='white')
    data = np.array(img, dtype=np.int64)
    return data


def size_test():
    for patch_size in range(1, 60):
        payload = '0' * (patch_size ** 2)
        for v in range(1, 41):
            try:
                patch_qr = gen_qr(payload, version=v)
            except qrcode.exceptions.DataOverflowError:
                continue
            else:
                factor = patch_qr.shape[0] // patch_size
                left = patch_qr.shape[0] - factor * patch_size
                print(patch_size, patch_qr.shape, factor, patch_size - left)
                break

def generate(flag):
    data = gen_qr(flag, version=7, box_size=1)
    patch_size = 5

    patch_list = list()
    for i in range(0, data.shape[0], patch_size):
        for j in range(0, data.shape[1], patch_size):
            patch_list.append((i , j))

    # setup
    x, y = patch_list[0]
    patch_data = str(int(''.join([str(c) for c in list(data[x:x+patch_size, y:y+patch_size].flatten())]), 2))
    for v in range(1, 41):
        try:
            patch_qr = gen_qr(patch_data, version=v)
        except qrcode.exceptions.DataOverflowError:
            continue
        else:
            factor = patch_qr.shape[0] // patch_size
            padding = patch_qr.shape[0] - factor * patch_size
            if padding > 0:
                continue
            else:
                break

    # emplace
    large_data = np.repeat(np.repeat(data, factor, axis=0), factor, axis=1)
    for x, y in patch_list:
        patch_data = str(int(''.join([str(c) for c in list(data[x:x+patch_size, y:y+patch_size].flatten())]), 2))
        patch_qr = np.rot90(gen_qr(patch_data, version=v), k=random.randint(0, 3))
        large_data[x * factor : x * factor + patch_qr.shape[0], y * factor : y * factor + patch_qr.shape[1]] = patch_qr

    print(large_data.shape)
    imageio.imwrite('code.png', np.repeat(np.repeat(large_data, 4, axis=0), 4, axis=1) * 255)


if __name__ == '__main__':
    generate('GuardianCTF{qRc0d3_fr4cTa1}')
