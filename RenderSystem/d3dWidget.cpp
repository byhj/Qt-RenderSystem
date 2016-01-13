#include "d3dWidget.h"

#include <QTimer>

namespace byhj
{
	D3DWidget::D3DWidget(QWidget *parent /* = nullptr */)
		:QWidget(parent)
	{
		setAttribute(Qt::WA_PaintOnScreen, true);
		setAttribute(Qt::WA_NativeWindow, true);

		QTimer *pTimer =new QTimer(this);
		connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
		pTimer->start(20);
		m_hWnd = (HWND)this->winId();
	}

	D3DWidget::~D3DWidget()
	{

	}

	QPaintEngine * D3DWidget::paintEngine()  const
	{
		return NULL;
	}

	void D3DWidget::resizeEvent(QResizeEvent *ent)
	{
	}

	void D3DWidget::paintEvent(QPaintEvent *ent)
	{
		render();
	}

	void D3DWidget::init(int sw, int sh)
	{
		m_width = sw;
		m_height = sh;

		init_device();
		init_object();
		init_camera();
	}

	void D3DWidget::update()
	{

	}

	void D3DWidget::render()
	{
		float bgColor[4] ={ 0.2f, 0.3f, 0.4f, 1.0f };

		m_pD3D11DeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
		m_pD3D11DeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), bgColor);
		m_pD3D11DeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		
		m_Triangle.Render(m_pD3D11DeviceContext.Get(), m_Matrix);
		
		m_pSwapChain->Present(0, 0);
	}

	void D3DWidget::shutdown()
	{

	}
	
	void D3DWidget::init_device()
	{
		////////////////////////Create buffer desc////////////////////////////
		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
		bufferDesc.Width                   = m_width;
		bufferDesc.Height                  = m_height;
		bufferDesc.RefreshRate.Numerator   = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;

		//Create swapChain Desc
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapChainDesc.BufferDesc         = bufferDesc;
		swapChainDesc.SampleDesc.Count   = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount        = 1;
		swapChainDesc.OutputWindow       = m_hWnd;
		swapChainDesc.Windowed           = TRUE;
		swapChainDesc.SwapEffect         = DXGI_SWAP_EFFECT_DISCARD;


		///////////////////////////////////////////////////////////////////////////
		HRESULT hr;
		//Create the double buffer chain
		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
			NULL, NULL, NULL, NULL, D3D11_SDK_VERSION,
			&swapChainDesc, &m_pSwapChain, &m_pD3D11Device,
			NULL, &m_pD3D11DeviceContext);
		//DebugHR(hr);

		//Create back buffer, buffer also is a texture
		ID3D11Texture2D *pBackBuffer;
		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
		hr = m_pD3D11Device->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		pBackBuffer->Release();
		//DebugHR(hr);


		///////////////////////////Creaete Depth/Stencil Buffer/////////////////////////////////
		D3D11_TEXTURE2D_DESC depthStencilDesc;

		depthStencilDesc.Width              = m_width;
		depthStencilDesc.Height             = m_height;
		depthStencilDesc.MipLevels          = 1;
		depthStencilDesc.ArraySize          = 1;
		depthStencilDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count   = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage              = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags     = 0;
		depthStencilDesc.MiscFlags          = 0;

		m_pD3D11Device->CreateTexture2D(&depthStencilDesc, NULL, &m_pDepthStencilBuffer);
		m_pD3D11Device->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), NULL, &m_pDepthStencilView);
		m_pD3D11DeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
	}

	void D3DWidget::init_object()
	{
		m_Triangle.Init(m_pD3D11Device.Get(), m_pD3D11DeviceContext.Get(), m_hWnd);
	}

	void D3DWidget::init_camera()
	{
		//Viewport Infomation
		D3D11_VIEWPORT vp;
		ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.Width    = static_cast<FLOAT>(m_width);
		vp.Height   = static_cast<FLOAT>(m_height);
		m_pD3D11DeviceContext->RSSetViewports(1, &vp);

		auto aspect = vp.Width / vp.Height;

		//MVP Matrix
		XMVECTOR camPos    = XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f);
		XMVECTOR camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR camUp     = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		XMMATRIX View      = XMMatrixLookAtLH(camPos, camTarget, camUp);
		XMMATRIX Proj      = XMMatrixPerspectiveFovLH(0.4f*3.14f, aspect, 1.0f, 1000.0f);
		XMMATRIX Model     = XMMatrixIdentity();


		XMStoreFloat4x4(&m_Matrix.model, XMMatrixTranspose(Model));
		XMStoreFloat4x4(&m_Matrix.view, XMMatrixTranspose(View));
		XMStoreFloat4x4(&m_Matrix.proj, XMMatrixTranspose(Proj));
	}

}