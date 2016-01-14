#ifndef d3dWidget_H
#define d3dWidget_H

#include <Qtwidgets/QWidget>

#include <dxgi.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <assert.h>

#include <wrl.h>

#include "triangle.h"

using namespace Microsoft::WRL;

QT_BEGIN_NAMESPACE
class QResizeEvent;
class QPaintEvent;
QT_END_NAMESPACE;

namespace byhj
{
	class D3DWidget : public QWidget
	{
		Q_OBJECT

	public:
		D3DWidget(QWidget *parent = nullptr);
		~D3DWidget();

		virtual QPaintEngine * paintEngine() const override;
		void init(int sw, int sh);

	protected:
		virtual void resizeEvent(QResizeEvent *ent);
		virtual void paintEvent(QPaintEvent *ent);


		void update();
		void render();
		void shutdown();

	private:

		void init_device();
		void init_object();
		void init_camera();

		ComPtr<IDXGISwapChain> m_pSwapChain ;
		ComPtr<ID3D11Device>   m_pD3D11Device;
		ComPtr<ID3D11DeviceContext> m_pD3D11DeviceContext;
		ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
		ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
		ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer;
		d3d::MatrixBuffer m_Matrix;

		int m_width;
		int m_height;
		HWND m_hWnd;

		byhj::Triangle m_Triangle;
	};
}
#endif