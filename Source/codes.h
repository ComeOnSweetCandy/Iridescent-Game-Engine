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

//IEInteraction * t1 = (IEInteraction *)(scene->GetBindedMap()->GetThing()->AddChild(3, 2, 0, 0, 0));
//IEStateThing * t2 = (IEStateThing *)(scene->GetBindedMap()->GetThing()->AddChild(4, 4, 0, 0, 0));
//t1->BindStateThing(t2);

//IERay * ray = IERay::Create("ray/body.png", 6.0f, 45.0f);
//p->AddChild(ray);

//IEInteraction * t1 = (IEInteraction *)(scene->GetBindedMap()->GetThing()->AddChild(3, 2, 0, 0, 0));
//IEStateThing * t2 = (IEStateThing *)(scene->GetBindedMap()->GetThing()->AddChild(4, 4, 0, 0, 0));
//t1->BindStateThing(t2);

//scene->GetBindedMap()->GetTerrain()->SetReadyTerrain(1, __terrain_body_mode__);
//for (int x = -3; x < 3; x++)
//{
//	for (int y = -3; y < 3; y++)
//	{
//		scene->GetBindedMap()->GetTerrain()->AddChild(x, y);
//	}
//}

//scene->GetBindedMap()->GetMarble()->AddChild(0, 1, 1, true);

//IEPlayer * player = IEPlayer::Create(0);
//scene->AddChild(player);

//IETexturePacker * packer = IETexturePacker::Create("testWall");
//
//packer->AddImage("../Debug/data/texture/wall/body.png", "body", "normal", 0.0f, 0);
//
//packer->AddImage("../Debug/data/texture/wall/end_0.png", "end_0", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/end_1.png", "end_1", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/end_2.png", "end_2", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/end_3.png", "end_3", "normal", 0.0f, 0);
//
//packer->AddImage("../Debug/data/texture/wall/line_0.png", "line_0", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/line_1.png", "line_1", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/line_2.png", "line_2", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/line_3.png", "line_3", "normal", 0.0f, 0);
//
//packer->AddImage("../Debug/data/texture/wall/corner_0.png", "corner_0", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/corner_1.png", "corner_1", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/corner_2.png", "corner_2", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/corner_3.png", "corner_3", "normal", 0.0f, 0);
//
//packer->AddImage("../Debug/data/texture/wall/fork_0.png", "fork_0", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/fork_1.png", "fork_1", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/fork_2.png", "fork_2", "normal", 0.0f, 0);
//packer->AddImage("../Debug/data/texture/wall/fork_3.png", "fork_3", "normal", 0.0f, 0);
//
//packer->AddImage("../Debug/data/texture/wall/cross.png", "cross", "normal", 0.0f, 0);
//
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

//IECreature * creature = IECreature::Create(1, 1);
//creature->GetCreatureUnit()->_Party = __creature_party_enemy__;
//scene->AddChild(creature);
//IEPlayer * player = IEPlayer::Create(1);
//player->SetPosition(0, 0);
//scene->AddChild(player);