uint32_t BeanVertexCount = 0;
SceneVertex* BeanVertices = NULL;
uint32_t BeanIndexCount = 0;
uint32_t* BeanIndices = NULL;

void CalculateRing(uint32_t Segments, float r, float y, float dy, float Radius, float Height) 
{
	float SegmentIncrease = 1.0 / (Segments - 1);

	for (uint32_t s = 0; s < Segments; s++) 
	{
		BeanVertices = (SceneVertex*)realloc(BeanVertices, (BeanVertexCount + 1) * sizeof(SceneVertex));

		float x = -cosf((PI * 2) * s * SegmentIncrease) * r;
		float z = sinf((PI * 2) * s * SegmentIncrease) * r;

		BeanVertices[BeanVertexCount].Pos = Vec3(Radius * x, Radius * y + Height * dy, Radius * z);
		BeanVertices[BeanVertexCount].Normal = Vec3(x, y, z);
		BeanVertices[BeanVertexCount].Color = Vec3f(1.0);

		float u = (s * SegmentIncrease);
		float v = 0.5 - ((Radius * y + Height * dy) / (2.0 * Radius + Height));
		BeanVertices[BeanVertexCount].TexCoord = Vec2(u, 1.0 - v);

		BeanVertexCount++;
	}
}

void CreateBean(uint32_t Segments, uint32_t SubdivisionsHeight)
{
	BeanVertexCount = 0;
	BeanIndexCount = 0;
	
	float Radius = 0.5;
	float Height = Radius * 2;

	uint32_t RingsBody = SubdivisionsHeight + 1;
	uint32_t RingsTotal = SubdivisionsHeight + RingsBody;


	float BodyIncrease = 1.0 / (RingsBody - 1);
	float RingIncrease = 1.0 / (SubdivisionsHeight - 1);
	for (uint32_t r = 0; r < SubdivisionsHeight * 0.5; r++)
		CalculateRing(Segments, sinf(PI * r * RingIncrease), sinf(PI * (r * RingIncrease - 0.5)), -0.5, Radius, Height);

	for (uint32_t r = 0; r < RingsBody; r++)
		CalculateRing(Segments, 1.0, 0.0, r * BodyIncrease - 0.5, Radius, Height);

	for (uint32_t r = SubdivisionsHeight * 0.5; r < SubdivisionsHeight; r++)
		CalculateRing(Segments, sinf(PI * r * RingIncrease), sinf(PI * (r * RingIncrease - 0.5)), 0.5, Radius, Height);

	for (uint32_t r = 0; r < RingsTotal - 1; r++) 
	{
		for (uint32_t s = 0; s < Segments - 1; s++) 
		{
			BeanIndices = (uint32_t*)realloc(BeanIndices, (BeanIndexCount + 6) * sizeof(uint32_t));

			BeanIndices[BeanIndexCount] = r * Segments + (s + 1);
			BeanIndices[BeanIndexCount + 1] = r * Segments + (s + 0);
			BeanIndices[BeanIndexCount + 2] = (r + 1) * Segments + (s + 1);
			
			BeanIndices[BeanIndexCount + 3] = (r + 1) * Segments + (s + 0);
			BeanIndices[BeanIndexCount + 4] = (r + 1) * Segments + (s + 1);
			BeanIndices[BeanIndexCount + 5] = (r * Segments + s);

			BeanIndexCount += 6;
		}
	}
}
