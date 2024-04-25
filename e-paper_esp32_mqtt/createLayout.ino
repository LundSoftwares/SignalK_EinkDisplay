void createLayout()
{
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.fillScreen(GxEPD_WHITE);
  display.drawBitmap(sealine_logo, 2, 2, 110, 40, GxEPD_BLACK);
  //display.setTextSize(2);
  display.drawLine(199,60,199,295,GxEPD_BLACK);
  display.drawLine(200,60,200,295,GxEPD_BLACK);
  //display.drawLine(151,60,151,295,GxEPD_BLACK);
 // display.drawChar(10,20,0xF8,GxEPD_BLACK,GxEPD_WHITE,1,1);

  display.setFont(&FreeSans9pt7b);
  display.setCursor(270, 20);
  display.print("Updated:");
  display.setCursor(346, 20);
  display.print(latestUpdate);

  display.setCursor(270, 40);
  display.print("Page:");
  display.setCursor(346, 40);
  if(PageSelectState == 0)
  {
    //-------------- PAGE 1 --------------------
    display.print("1");
    display.setFont(&FreeSansBold9pt7b);
  
    //Column 1
    display.setCursor(col1, row1);
    display.print(col1row1);
    display.setCursor(col2, row1);
    display.print(col2row1); 
    display.setCursor(col1, row2);
    display.print(col1row2);
    display.setCursor(col2, row2);
    display.print(col2row2); 
    display.setCursor(col1,row3);
    display.print(col1row3);
    display.setCursor(col2, row3);
    display.print(col2row3);  
    display.setCursor(col1, row4);
    display.print(col1row4);
    display.setCursor(col2, row4);
    display.print(col2row4); 
    display.setCursor(col1, row5);
    display.print(col1row5);
    display.setCursor(col2, row5);
    display.print(col2row5); 
    display.setCursor(col1, row6);
    display.print(col1row6);
    display.setCursor(col2, row6);
    display.print(col2row6);
    display.setCursor(col1, row7);
    display.print(col1row7);
    display.setCursor(col2, row7);
    display.print(col2row7);
    display.setCursor(col1, row8);
    display.print(col1row8);
    display.setCursor(col2, row8);
    display.print(col2row8);
    display.setCursor(col1, row9);
    display.print(col1row9);
    display.setCursor(col2, row9);
    display.print(col2row9);
  
    //Column 2
    display.setCursor(col3, row1);
    display.print(col3row1);
    display.setCursor(col4, row1);
    display.print(col4row1); 
    display.setCursor(col3, row2);
    display.print(col3row2);
    display.setCursor(col4, row2);
    display.print(col4row2); 
    display.setCursor(col3, row3);
    display.print(col3row3);
    display.setCursor(col4, row3);
    display.print(col4row3);  
    display.setCursor(col3, row4);
    display.print(col3row4);
    display.setCursor(col4, row4);
    display.print(col4row4); 
    display.setCursor(col3, row5);
    display.print(col3row5);
    display.setCursor(col4, row5);
    display.print(col4row5); 
    display.setCursor(col3, row6);
    display.print(col3row6);
    display.setCursor(col4, row6);
    display.print(col4row6); 
    display.setCursor(col3, row7);
    display.print(col3row7);
    display.setCursor(col4, row7);
    display.print(col4row7); 
    display.setCursor(col3, row8);
    display.print(col3row8);
    display.setCursor(col4, row8);
    display.print(col4row8); 
    display.setCursor(col3, row9);
    display.print(col3row9);
    display.setCursor(col4, row9);
    display.print(col4row9);
  }
  else
  {
    // ----------------------- PAGE 2 --------------------------
    display.print("2");
    display.setFont(&FreeSansBold9pt7b);
  
    //Column 1
    display.setCursor(col1, row1);
    display.print(p2col1row1);
    display.setCursor(col2, row1);
    display.print(p2col2row1); 
    display.setCursor(col1, row2);
    display.print(p2col1row2);
    display.setCursor(col2, row2);
    display.print(p2col2row2); 
    display.setCursor(col1,row3);
    display.print(p2col1row3);
    display.setCursor(col2, row3);
    display.print(p2col2row3);  
    display.setCursor(col1, row4);
    display.print(p2col1row4);
    display.setCursor(col2, row4);
    display.print(p2col2row4); 
    display.setCursor(col1, row5);
    display.print(p2col1row5);
    display.setCursor(col2, row5);
    display.print(p2col2row5); 
    display.setCursor(col1, row6);
    display.print(p2col1row6);
    display.setCursor(col2, row6);
    display.print(p2col2row6);
    display.setCursor(col1, row7);
    display.print(p2col1row7);
    display.setCursor(col2, row7);
    display.print(p2col2row7);
    display.setCursor(col1, row8);
    display.print(p2col1row8);
    display.setCursor(col2, row8);
    display.print(p2col2row8);
    display.setCursor(col1, row9);
    display.print(p2col1row9);
    display.setCursor(col2, row9);
    display.print(p2col2row9);
  
    //Column 2
    display.setCursor(col3, row1);
    display.print(p2col3row1);
    display.setCursor(col4, row1);
    display.print(p2col4row1); 
    display.setCursor(col3, row2);
    display.print(p2col3row2);
    display.setCursor(col4, row2);
    display.print(p2col4row2); 
    display.setCursor(col3, row3);
    display.print(p2col3row3);
    display.setCursor(col4, row3);
    display.print(p2col4row3);  
    display.setCursor(col3, row4);
    display.print(p2col3row4);
    display.setCursor(col4, row4);
    display.print(p2col4row4); 
    display.setCursor(col3, row5);
    display.print(p2col3row5);
    display.setCursor(col4, row5);
    display.print(p2col4row5); 
    display.setCursor(col3, row6);
    display.print(p2col3row6);
    display.setCursor(col4, row6);
    display.print(p2col4row6); 
    display.setCursor(col3, row7);
    display.print(p2col3row7);
    display.setCursor(col4, row7);
    display.print(p2col4row7); 
    display.setCursor(col3, row8);
    display.print(p2col3row8);
    display.setCursor(col4, row8);
    display.print(p2col4row8); 
    display.setCursor(col3, row9);
    display.print(p2col3row9);
    display.setCursor(col4, row9);
    display.print(p2col4row9);
  }
  
  
 
}
