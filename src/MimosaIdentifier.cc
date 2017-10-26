
#include "MimosaIdentifier.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MimosaIdentifier::MimosaIdentifier(int layer,int ladder,int chip,int column,int row){

  mimosaGeo=MimosaGeoParameter::GetGeo();
  m_pixelId = 0;

  m_layerId=layer;
  m_ladderId=ladder;
  m_chipId=chip;
  m_columnId=column;
  m_rowId=row;

  int nofChip=(mimosaGeo->Layer(layer)).ChipNo();
  int nofPix=(mimosaGeo->Layer(layer)).PixNo();
  int nofCol=mimosaGeo->Layer(layer).ColNo();
  m_globalChipId=ladder*nofChip+chip;
  m_pixelId=(ladder*nofChip+chip)*nofPix+row*nofCol+column;

  for(int i=0;i<layer;++i){
    m_pixelId += (mimosaGeo->Layer(i)).LayerPixNo();
  }

}

void MimosaIdentifier::WhichPixel(double posX, double posY){
  //m_rowId = int(posY/(mimosaGeo->Layer(0).PitchY() *um)) + int(mimosaGeo->Layer(0).RowNo()/2);
  //m_columnId = int(posX/(mimosaGeo->Layer(0).PitchX() *um)) + int(mimosaGeo->Layer(0).ColNo()/2);

  int nofChip=(mimosaGeo->Layer(m_layerId)).ChipNo();
  int nofPix=(mimosaGeo->Layer(m_layerId)).PixNo();
  int nofCol=mimosaGeo->Layer(m_layerId).ColNo();
  int nofRow=mimosaGeo->Layer(m_layerId).RowNo();
  double pixPitchX=mimosaGeo->Layer(0).PitchX() *um;
  double pixPitchY=mimosaGeo->Layer(0).PitchY() *um;
  double sensorSizeX=pixPitchX*nofCol;
  double sensorSizeY=pixPitchY*nofRow;

  m_rowId = int((posY+(sensorSizeY/2.))/pixPitchY);
  m_columnId = int((posX+(sensorSizeX/2.))/pixPitchX);

  m_pixelId=(m_ladderId*nofChip+m_chipId)*nofPix+m_rowId*nofCol+m_columnId;
  for(int i=0;i<m_layerId;++i){
    m_pixelId += (mimosaGeo->Layer(i)).LayerPixNo();
  }
  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreeVector MimosaIdentifier::PixelPos(){
  int nofCol=mimosaGeo->Layer(m_layerId).ColNo();
  int nofRow=mimosaGeo->Layer(m_layerId).RowNo();
  double pixPitchX=mimosaGeo->Layer(0).PitchX() *um;
  double pixPitchY=mimosaGeo->Layer(0).PitchY() *um;
  double sensorSizeX=pixPitchX*nofCol;
  double sensorSizeY=pixPitchY*nofRow;
  double posX=(m_columnId+0.5)*pixPitchX-(sensorSizeX/2.);
  double posY=(m_rowId+0.5)*pixPitchY-(sensorSizeY/2.);
  double posZ=0;
  G4ThreeVector pos(posX,posY,posZ);
  return pos;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MimosaIdentifier::Print(){
  G4cout<<"MimosaID::Layer: "<<m_layerId<<" Ladder: "<<m_ladderId<<" Chip: "<<m_chipId<<" Column: "<<m_columnId<<" Row: "<<m_rowId<<" Pixel: "<<m_pixelId<<G4endl;
}
