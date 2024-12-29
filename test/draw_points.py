import sys
from PIL import Image

def draw_points_from_file(input_path, output_path):
    """
    テキストファイル (top, right形式) を読み込み、
    各点を黒で塗った画像を生成して保存する。
    """

    # 1) テキストファイルから読み込む
    points = []
    with open(input_path, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue  # 空行などはスキップ
            # "top, right" を分割
            right_str, top_str = line.split(',')
            top = int(top_str.strip())
            right = int(right_str.strip())
            points.append((top, right))

    if not points:
        print("座標データがありません。")
        return

    # 2) 最小・最大座標を調べる
    min_top = min(p[0] for p in points)
    max_top = max(p[0] for p in points)
    min_right = min(p[1] for p in points)
    max_right = max(p[1] for p in points)

    # 画像の大きさを決める
    # 座標の範囲分 +1 ピクセルで確保する
    width  = (max_right - min_right) + 1
    height = (max_top - min_top) + 1

    # 3) Pillowで画像を新規作成 (RGB, 背景は白)
    img = Image.new("RGB", (width, height), "white")

    # 4) 画像上に点を描画する
    #    「top」は画像の y座標、「right」は x座標 として扱う
    pixels = img.load()
    for (top, right) in points:
        # ファイルに書かれている座標がそのまま使えるように
        # (min_top, min_right) を原点(0,0)とする。
        y = top - min_top
        x = right - min_right

        # 範囲外チェック（通常は不要だが安全のため）
        if 0 <= x < width and 0 <= y < height:
            # ピクセルを黒に
            pixels[x, y] = (0, 0, 0)

    # 5) 画像を保存
    img.save(output_path)
    print(f"画像を保存しました: {output_path}")


if __name__ == "__main__":
    """
    使い方:
    python draw_points.py <入力ファイル> <出力画像ファイル>
    例: python draw_points.py points.txt result.png
    """
    if len(sys.argv) < 3:
        print("Usage: python draw_points.py <入力テキストファイル> <出力画像ファイル>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]
    draw_points_from_file(input_file, output_file)

