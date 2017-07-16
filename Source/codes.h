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

//IEImage * images[10];
//for (int i = 0; i < 10; i++)
//{
//	images[i] = IEImage::Create();
//}
//images[0]->LoadImageData("../Debug/data/texture/other/fire/body_0.png");
//images[1]->LoadImageData("../Debug/data/texture/other/fire/body_1.png");
//images[2]->LoadImageData("../Debug/data/texture/other/fire/body_2.png");
//images[3]->LoadImageData("../Debug/data/texture/other/fire/body_3.png");
//images[4]->LoadImageData("../Debug/data/texture/other/fire/body_0.png");
//images[5]->LoadImageData("../Debug/data/texture/other/fire/body_1.png");
//images[6]->LoadImageData("../Debug/data/texture/other/fire/body_2.png");
//images[7]->LoadImageData("../Debug/data/texture/other/fire/body_3.png");
//images[8]->LoadImageData("../Debug/data/texture/other/fire/icon_0.png");
//images[9]->LoadImageData("../Debug/data/texture/other/fire/picked_0.png");
//
//IETexturePacker * packer = IETexturePacker::Create("torch");
//packer->AddImage(images[0], "body", 0.2f, 0);
//packer->AddImage(images[1], "body", 0.5f, 0);
//packer->AddImage(images[2], "body", 0.7f, 0);
//packer->AddImage(images[3], "body", 1.0f, 0);
//packer->AddImage(images[4], "body", 0.2f, 1);
//packer->AddImage(images[5], "body", 0.5f, 1);
//packer->AddImage(images[6], "body", 0.7f, 1);
//packer->AddImage(images[7], "body", 1.0f, 1);
//packer->AddImage(images[8], "icon", 2.0f, 0);
//packer->AddImage(images[9], "picked", 2.0f, 0);
//packer->SaveTexture();
//packer->ReleaseDisreference();

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