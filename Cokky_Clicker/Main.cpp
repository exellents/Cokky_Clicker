# include <Siv3D.hpp>

/// @brief アイテムのボタン
/// @param rect ボタンの領域
/// @param texture ボタンの絵文字
/// @param font 文字描画に使うフォント
/// @param name アイテムの名前
/// @param desc アイテムの説明
/// @param count アイテムの所持数
/// @param enabled ボタンを押せるか
/// @return ボタンが押された場合 true, それ以外の場合は false
bool Button(const Rect& rect, const Texture& texture, const Font& font, const String& name, const String& desc, int32 count, bool enabled)
{
	if (enabled)
	{
		rect.draw(ColorF{ 0.3, 0.5, 0.9, 0.8 });

		rect.drawFrame(2, 2, ColorF{ 0.5, 0.7, 1.0 });

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}
	else
	{
		rect.draw(ColorF{ 0.0, 0.4 });

		rect.drawFrame(2, 2, ColorF{ 0.5 });
	}

	texture.scaled(0.5).drawAt(rect.x + 50, rect.y + 50);

	font(name).draw(30, rect.x + 100, rect.y + 15, Palette::White);

	font(desc).draw(18, rect.x + 102, rect.y + 60, Palette::White);

	font(count).draw(50, Arg::rightCenter((rect.x + rect.w - 20), (rect.y + 50)), Palette::White);

	return (enabled && rect.leftClicked());
}

bool emoji(const Rect& rect, const Texture& emoji, bool enabled)
{
	if (enabled)
	{
		rect.draw(ColorF{ 0.9, 0.3, 0.3, 0.8 });

		rect.drawFrame(2, 2, ColorF{ 1.0, 0.5, 0.5 });

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}
	else
	{
		rect.draw(ColorF{ 0.0, 0.4 });

		rect.drawFrame(2, 2, ColorF{ 0.5 });
	}

	if (enabled && rect.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	emoji.scaled(0.5).drawAt(rect.x + 50, rect.y + 50);

	return (enabled && rect.leftClicked());
}

bool shop(const Rect& rect, const Texture& emoji, const Font& font, const String& desc, bool enabled1, bool enabled2)
{
	if (enabled1)
	{
		rect.draw(ColorF{ 0.9, 0.3, 0.3, 0.8 });

		rect.drawFrame(2, 2, ColorF{ 1.0, 0.5, 0.5 });

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}
	else if (enabled2)
	{
		rect.draw(ColorF{ 0.3, 0.5, 0.9, 0.8 });

		rect.drawFrame(2, 2, ColorF{ 0.5, 0.7, 1.0 });

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}
	else
	{
		rect.draw(ColorF{ 0.0, 0.4 });

		rect.drawFrame(2, 2, ColorF{ 0.5 });
	}

	if (enabled1 && rect.mouseOver() || enabled2 && rect.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	emoji.scaled(0.5).drawAt(rect.x + 50, rect.y + 50);

	if (enabled1==false)
	{
		font(desc).draw(18, rect.x + 20, rect.y + 75, Palette::White);
	}

	return (enabled1 && rect.leftClicked() || enabled2 && rect.leftClicked());
}

void Main()
{
	// クッキーの絵文字
	const Texture texture{ U"😅"_emoji };
	const Texture texture2{ U"🤔"_emoji };
	const Texture texture3{ U"🥹"_emoji };
	const Texture texture4{ U"🤗"_emoji };
	const Texture texture5{ U"🤣"_emoji };
	const Texture texture6{ U"🤪"_emoji };
	const Texture texture7{ U"🤓"_emoji };
	const Texture texture8{ U"🥰"_emoji };
	const Texture texture9{ U"🫨"_emoji };

	// 農場の絵文字
	const Texture farmEmoji{ U"🌾"_emoji };

	// 工場の絵文字
	const Texture factoryEmoji{ U"🏭"_emoji };

	// フォント
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// クッキーのクリック円
	const Circle cookieCircle{ 170, 300, 100 };

	// クッキーの表示サイズ（倍率）
	double cookieScale = 1.5;

	// クッキーの個数
	double cookies = 0;

	// 農場の所有数
	int32 farmCount = 0;

	// 工場の所有数
	int32 factoryCount = 0;

	// 農場の価格
	int32 farmCost = 10;

	// 工場の価格
	int32 factoryCost = 100;

	// ゲームの経過時間の蓄積
	double accumulatedTime = 0.0;

	int32 level = 0;

	int32 skin = 0;

	bool x = false;
	bool y = false;
	bool z = false;

	while (System::Update())
	{
		// クッキーの毎秒の生産量 (cookies per second) を計算する
		const int32 cps = (farmCount + factoryCount * 10);

		// ゲームの経過時間を加算する
		accumulatedTime += Scene::DeltaTime();

		// 0.1 秒以上蓄積していたら
		if (0.1 <= accumulatedTime)
		{
			accumulatedTime -= 0.1;

			// 0.1 秒分のクッキー生産を加算する
			cookies += (cps * 0.1);
		}

		// 農場の価格を計算する
		farmCost = 10 + (farmCount * 10);

		// 工場の価格を計算する
		factoryCost = 100 + (factoryCount * 100);

		// クッキー円上にマウスカーソルがあれば
		if (cookieCircle.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		// クッキー円が左クリックされたら
		if (cookieCircle.leftClicked())
		{
			cookieScale = 1.3;
			++cookies;
		}
		if (MouseM.pressed())
		{
			cookieScale = 1.3;
			cookies+=100;
		}

		// クッキーの表示サイズを回復する
		cookieScale += Scene::DeltaTime();

		if (1.5 < cookieScale)
		{
			cookieScale = 1.5;
		}

		// 背景を描く
		Rect{ 0, 0, 800, 600 }.draw(Arg::top = ColorF{ 0.6, 0.5, 0.3 }, Arg::bottom = ColorF{ 0.2, 0.5, 0.3 });

		// クッキーの数を整数で表示する
		font(U"{:.0f}"_fmt(cookies)).drawAt(60, 170, 100);

		// クッキーの生産量を表示する
		font(U"毎秒: {}"_fmt(cps)).drawAt(24, 170, 160);

		// クッキーを描画する
		if (skin == 0)
		{
			texture.scaled(cookieScale).drawAt(cookieCircle.center);
		}

		if (skin ==1)
		{
			texture2.scaled(cookieScale).drawAt(cookieCircle.center);
		}

		if (skin == 2)
		{
			texture3.scaled(cookieScale).drawAt(cookieCircle.center);
		}

		if (skin == 3)
		{
			texture4.scaled(cookieScale).drawAt(cookieCircle.center);
		}

		if (skin == 4)
		{
			texture5.scaled(cookieScale).drawAt(cookieCircle.center);
		}

		if (skin == 5)
		{
			texture6.scaled(cookieScale).drawAt(cookieCircle.center);
		}

		if (skin == 6)
		{
			texture7.scaled(cookieScale).drawAt(cookieCircle.center);
		}

		if (skin == 7)
		{
			texture8.scaled(cookieScale).drawAt(cookieCircle.center);
		}

		if (skin == 8)
		{
			texture9.scaled(cookieScale).drawAt(cookieCircle.center);
		}

		if (cps < 10&&level==0)
		{
			if (level == 0)
			{
				skin = 0;
			}
			level = 1;
		}
		if (cps >= 10&&level==1)
		{
			if (level == 1)
			{
				skin = 1;
			}
			level = 2;
		}
		if (cps >= 50 && level == 2)
		{
			if (level == 2)
			{
				skin = 2;
			}
			level = 3;
		}
		if (cps >= 100 && level == 3)
		{
			if (level == 3)
			{
				skin = 3;
			}
			level = 4;
		}
		if (cps >= 200 && level == 4)
		{
			if (level == 4)
			{
				skin = 4;
			}
			level = 5;
		}
		if (cps >= 300 && level == 5)
		{
			if (level == 5)
			{
				skin = 5;
			}
			level = 6;
		}


		// 農場ボタン
		if (Button(Rect{ 340, 20, 420, 100 }, farmEmoji, font, U"クッキー農場", U"C{} / 1 CPS"_fmt(farmCost), farmCount, (farmCost <= cookies)))
		{
			cookies -= farmCost;
			++farmCount;
		}

		// 工場ボタン
		if (Button(Rect{ 340, 140, 420, 100 }, factoryEmoji, font, U"クッキー工場", U"C{} / 10 CPS"_fmt(factoryCost), factoryCount, (factoryCost <= cookies)))
		{
			cookies -= factoryCost;
			++factoryCount;
		}

		if (emoji(Rect{ 340, 260, 100, 100 }, texture, (level >= 1)))
		{
			skin = 0;
		}

		if (emoji(Rect{ 505, 260, 100, 100 }, texture2, (level >= 2)))
		{
			skin = 1;
		}

		if (emoji(Rect{ 660, 260, 100, 100 }, texture3, (level >= 3)))
		{
			skin = 2;
		}

		if (emoji(Rect{ 340, 380, 100, 100 }, texture4, (level >= 4)))
		{
			skin = 3;
		}

		if (emoji(Rect{ 505, 380, 100, 100 }, texture5, (level >= 5)))
		{
			skin = 4;
		}

		if (emoji(Rect{ 660, 380, 100, 100 }, texture6, (level >= 6)))
		{
			skin = 5;
		}

		if (shop(Rect{ 340, 500, 100, 100 }, texture7, font, U"C5000", (x == true), (5000 <= cookies)))
		{
			if (x == false)
			{
				cookies -= 5000;
				x = true;
			}
			skin = 6;
		}

		if (shop(Rect{ 505, 500, 100, 100 }, texture8, font, U"C5000", (y == true), (5000 <= cookies)))
		{
			if (y == false)
			{
				cookies -= 5000;
				y = true;
			}
			skin = 7;
		}

		if (shop(Rect{ 660, 500, 100, 100 }, texture9, font, U"C5000", (z == true), (5000 <= cookies)))
		{
			if (z == false)
			{
				cookies -= 5000;
				z = true;
			}
			skin = 8;
		}

	}
}
