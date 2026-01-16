#include "CameraGame.h"	
#include "Main.h"
#include "Player.h"
#include "Input.h"

constexpr float ce_fRadXZ = 0.0f;
constexpr float ce_fRadY = DirectX::XMConvertToRadians(135.0f);
constexpr float ce_fRadius = 40.0f;

CCameraGame::CCameraGame()
{
	m_f3Look = DirectX::XMFLOAT3(0.0f,0.0f,0.0f);
	
	m_f3Pos.x = cosf(ce_fRadY) * sinf(ce_fRadXZ) * ce_fRadius + m_f3Look.x;
	m_f3Pos.y = sinf(ce_fRadY) * ce_fRadius + m_f3Look.y;
	m_f3Pos.z = cosf(ce_fRadY) * cosf(ce_fRadXZ) * ce_fRadius + m_f3Look.z;
}

CCameraGame::~CCameraGame()
{

}

void CCameraGame::Update()
{
	DirectX::XMFLOAT3 f3PlayerPos = GetScene()->GetGameObject<CPlayer>()->GetPos();
	m_f3Look = f3PlayerPos;

	m_f3Pos.x = cosf(ce_fRadY) * sinf(ce_fRadXZ) * ce_fRadius + m_f3Look.x;
	m_f3Pos.y = sinf(ce_fRadY) * ce_fRadius + m_f3Look.y;
	m_f3Pos.z = cosf(ce_fRadY) * cosf(ce_fRadXZ) * ce_fRadius + m_f3Look.z;
}

DirectX::XMFLOAT3 CCameraGame::GetClickTarget()
{
	POINT* pMousePos = GetMousePosition(true);
	DirectX::XMMATRIX mousePosMat = DirectX::XMMatrixTranslation((float)pMousePos->x, (float)pMousePos->y, 0.0f);

	// カメラのビュー行列を取得
	DirectX::XMFLOAT4X4 cameraView = CCamera::GetInstance()->GetViewMatrix(false);
	DirectX::XMMATRIX cameraViewMat = DirectX::XMLoadFloat4x4(&cameraView);
	// カメラのビュー行列の逆行列を計算
	DirectX::XMMATRIX invViewMat = DirectX::XMMatrixInverse(nullptr, cameraViewMat);

	// カメラのプロジェクション行列を取得
	DirectX::XMFLOAT4X4 cameraProj = CCamera::GetInstance()->GetProjectionMatrix(false);
	DirectX::XMMATRIX cameraProjMat = DirectX::XMLoadFloat4x4(&cameraProj);
	// カメラのプロジェクション行列の逆行列を計算
	DirectX::XMMATRIX invProjMat = DirectX::XMMatrixInverse(nullptr, cameraProjMat);

	// スクリーン座標からワールド座標への変換
	DirectX::XMMATRIX worldPosMat = mousePosMat * invProjMat;
	// ワールド座標を取得
	worldPosMat *= invViewMat;

	// 位置ベクトルを抽出
	DirectX::XMFLOAT3 worldPos;
	DirectX::XMStoreFloat3(&worldPos, worldPosMat.r[3]);

	return worldPos;
}
