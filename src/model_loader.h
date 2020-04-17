#pragma once

#include "dx12_labs.h"
#include "tiny_obj_loader.h"

struct DrawCallParams
{
	UINT index_num;
	UINT start_index;
	UINT start_vertex;
};

class ModelLoader {
public:
	ModelLoader();
	~ModelLoader();

	HRESULT LoadModel(std::string path);

	const FullVertex* GetVertexBuffer() const;
	const UINT GetVertexBufferSize() const;
	const UINT GetVertexNum() const;

	const UINT* GetIndexBuffer() const;
	const UINT GetIndexBufferSize() const;
	const UINT GetIndexNum() const;

	const UINT GetMaterialNum() const;
	const DrawCallParams GetDrawCallParams(UINT material_id) const;

protected:
	std::vector<FullVertex> verteces;
	std::vector<UINT> indeces;
	std::string model_dir;
	std::vector<tinyobj::material_t> materials;
};