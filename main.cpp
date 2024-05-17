#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<assert.h>

const char kWindowTitle[] = "学籍番号";

struct Matrix4x4 {
	float m[4][4];
};

struct Vector3 {
	float x, y, z;
};

//1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 matrixAnswer;
	matrixAnswer.m[0][0] = 1;
	matrixAnswer.m[0][1] = 0;
	matrixAnswer.m[0][2] = 0;
	matrixAnswer.m[0][3] = 0;
	matrixAnswer.m[1][0] = 0;
	matrixAnswer.m[1][1] = 1;
	matrixAnswer.m[1][2] = 0;
	matrixAnswer.m[1][3] = 0;
	matrixAnswer.m[2][0] = 0;
	matrixAnswer.m[2][1] = 0;
	matrixAnswer.m[2][2] = 1;
	matrixAnswer.m[2][3] = 0;
	matrixAnswer.m[3][0] = translate.x;
	matrixAnswer.m[3][1] = translate.y;
	matrixAnswer.m[3][2] = translate.z;
	matrixAnswer.m[3][3] = 1;
	return matrixAnswer;
}

//2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 matrixAnswer;
	matrixAnswer.m[0][0] = scale.x;
	matrixAnswer.m[0][1] = 0;
	matrixAnswer.m[0][2] = 0;
	matrixAnswer.m[0][3] = 0;
	matrixAnswer.m[1][0] = 0;
	matrixAnswer.m[1][1] = scale.y;
	matrixAnswer.m[1][2] = 0;
	matrixAnswer.m[1][3] = 0;
	matrixAnswer.m[2][0] = 0;
	matrixAnswer.m[2][1] = 0;
	matrixAnswer.m[2][2] = scale.z;
	matrixAnswer.m[2][3] = 0;
	matrixAnswer.m[3][0] = 0;
	matrixAnswer.m[3][1] = 0;
	matrixAnswer.m[3][2] = 0;
	matrixAnswer.m[3][3] = 1;
	return matrixAnswer;
}

//3.座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 vectorAnswer;
	vectorAnswer.x = vector.x * matrix.m[0][0]
					+ vector.y * matrix.m[1][0]
					+ vector.z * matrix.m[2][0]
					+ 1.0f * matrix.m[3][0];
	vectorAnswer.y = vector.x * matrix.m[0][1]
					+ vector.y * matrix.m[1][1]
					+ vector.z * matrix.m[2][1]
					+ 1.0f * matrix.m[3][1];
	vectorAnswer.z = vector.x * matrix.m[0][2]
					+ vector.y * matrix.m[1][2]
					+ vector.z * matrix.m[2][2]
					+ 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3]
					+ vector.y * matrix.m[1][3]
					+ vector.z * matrix.m[2][3]
					+ 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	vectorAnswer.x /= w;
	vectorAnswer.y /= w;
	vectorAnswer.z /= w;
	return vectorAnswer;
}



Matrix4x4 MakeTranslateMatrix(const Vector3& translate);


Matrix4x4 MakeScaleMatrix(const Vector3& scale);


Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

Vector3 translate{ 4.1f,2.6f,0.8f };
Vector3 scale{ 1.5f,5.2f,7.3f };
Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
Vector3 point{ 2.3f,3.8f,1.4f };
Matrix4x4 transformMatrix = {
	1.0f,2.0f,3.0f,4.0f,
	3.0f,1.0f,1.0f,2.0f,
	1.0f,4.0f,2.0f,3.0f,
	2.0f,2.0f,1.0f,3.0f
};

Vector3 transformed = Transform(point, transformMatrix);

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix,const char[]) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector,const char[]) {
	Novice::ScreenPrintf(x + 0 * kColumnWidth, y + 1 * kRowHeight, "%6.02f", vector.x);
	Novice::ScreenPrintf(x + 1 * kColumnWidth, y + 1 * kRowHeight, "%6.02f", vector.y);
	Novice::ScreenPrintf(x + 2 * kColumnWidth, y + 1 * kRowHeight, "%6.02f", vector.z);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		Novice::ScreenPrintf(0, 0, "transformed");
		VectorScreenPrintf(0, 0, transformed, "transformed");
		Novice::ScreenPrintf(0, kRowHeight * 2, "translateMatrix");
		MatrixScreenPrintf(0, kRowHeight * 3, translateMatrix, "translateMatrix");
		Novice::ScreenPrintf(0, kRowHeight * 7, "scaleMatrix");
		MatrixScreenPrintf(0, kRowHeight * 8, scaleMatrix, "scaleMatrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

