////IEFontTTF::Create("", "../Debug/data/font/msyhbd.ttc", 20);
////IEFontTTF::Share()->WriteFontFile(65535, 256, "../Debug/data/font/font_0.tga", "../Debug/data/font/font_0.data");
//IEFontTTF::Share()->ReadFontFile("../Debug/data/font/font_0.tga", "../Debug/data/font/font_0.data");

//map = IEMap::Create("scene1");
//IEPlayer * player = IEPlayer::Create(0);
//player->SetPosition(0.0f, 0.0f);
//IECreature * enemy = IECreature::Create(0);
//enemy->SetPosition(2.0f, 0.0f);
//map->AddChild(player);
//map->AddChild(enemy);
//scene->AddChild(map);
//
//CreatePickedProp(10001, 20, -1, -1);
//CreatePickedProp(10002, 20, 1, -1);
//CreatePickedProp(20001, 8, -1, 1);
//
//IEUiLayer * ui = GetCurrentUILayer();
//IESlot * big = IESlot::Create();
//
//player->m_propPack->SetShortCut(big);
//
//big->SetWidgetAlign(WIDGET_ALIGN_LEFT | WIDGET_VERALIGN_BOTTOM);
//big->SetWidgetSize(706, 76);
//big->SetWidgetColor(0.2f, 0.2f, 0.2f);
//ui->AddWidgetChild(big);
//
//for (int index = 0; index < 10; index++)
//{
//	IESlotButton * sam = IESlotButton::Create(index);
//	sam->SetWidgetSize(64, 64);
//	sam->SetWidgetMargin(6, 0, 0, 6);
//	sam->SetWidgetColor(0.5f, 0.5f, 0.5f);
//	big->AddWidgetChild(sam);
//}
//
//scene->AddChild(map);

//for (int x = -12; x < 12; x++)
//{
//	for (int y = -12; y < 12; y++)
//	{
//		scene->GetBindedMap()->GetTerrain()->AddChild(0, __terrain_body_mode__, x, y);
//	}
//}
//scene->GetBindedMap()->GetThing()->AddChild(2, 0, 4, 0, 0);
//
//IEPlayer * p = IEPlayer::Create(0);
//p->SetPosition(-1.0f, 0.0f);
//scene->AddChild(p);

//IEInteractionThing * t1 = (IEInteractionThing *)(scene->GetBindedMap()->GetThing()->AddChild(3, 2, 0, 0, 0));
//IEStateThing * t2 = (IEStateThing *)(scene->GetBindedMap()->GetThing()->AddChild(4, 4, 0, 0, 0));
//t1->BindStateThing(t2);

//IERay * ray = IERay::Create("ray/body.png", 6.0f, 45.0f);
//p->AddChild(ray);

//IEInteractionThing * t1 = (IEInteractionThing *)(scene->GetBindedMap()->GetThing()->AddChild(3, 2, 0, 0, 0));
//IEStateThing * t2 = (IEStateThing *)(scene->GetBindedMap()->GetThing()->AddChild(4, 4, 0, 0, 0));
//t1->BindStateThing(t2);

//for (int x = -12; x < 12; x++)
//{
//	for (int y = -12; y < 12; y++)
//	{
//		scene->GetBindedMap()->GetMarble()->AddChild(1, x, y);
//	}
//}

//scene->GetBindedMap()->GetMarble()->AddChild(0, 1, 1, true);

//IEPlayer * player = IEPlayer::Create(0);
//scene->AddChild(player);

//IEImage * images[8];
//for (int i = 0; i < 8; i++)
//{
//	images[i] = IEImage::Create();
//}
//images[0]->LoadImageData(IEString("../Debug/data/texture/color/red_0.png"));
//images[1]->LoadImageData(IEString("../Debug/data/texture/color/grey_0.png"));
//images[2]->LoadImageData(IEString("../Debug/data/texture/color/blue_0.png"));
//images[3]->LoadImageData(IEString("../Debug/data/texture/color/origin_0.png"));
//images[4]->LoadImageData(IEString("../Debug/data/texture/color/red_0.png"));
//images[5]->LoadImageData(IEString("../Debug/data/texture/color/red_0.png"));
//images[6]->LoadImageData(IEString("../Debug/data/texture/color/red_0.png"));
//images[7]->LoadImageData(IEString("../Debug/data/texture/color/red_0.png"));
//
//IETexturePacker * packer = IETexturePacker::Create("nothing");
//packer->AddImage(images[0]);
//packer->AddImage(images[1]);
//packer->AddImage(images[2]);
//packer->AddImage(images[3]);
//packer->AddImage(images[4]);
//packer->AddImage(images[5]);
//packer->AddImage(images[6]);
//packer->AddImage(images[7]);
//
//IEContainer * aarray = packer->Run();
//packer->Save();

////
//IEXml * xml = IEXml::Create("terrain/soil.xml");
//IEXml * textureXML = xml->FindChild("texture");
//const char * textureName = textureXML->FindChild("tex")->ValueString();
//
//IETime::Share()->ReckonBegin();
//IEPackerTexture * texture = IEPackerTexture::Create(textureXML);
//
//IESprite * sprite = IESprite::Create();
//sprite->SetScale(0.4);
//scene->GetBindedMap()->AddChild(sprite);
//
//sprite->ChangeTexture(texture);