#include "cmenu.hpp"
#include "../backdrop.h"
#include <windows.h>
#include <Lmcons.h>
#include "..\cheats\misc\logs.h"
#include "../message_hit.h"
#include "../backdrop.h"

menu::menu() {
	area = rect_t(200, 200, 369, 382);
	text = rect_t(150, 150, 369, 390);
}

void menu::render() {
	// lambda to handle outlines

	render::get().rect_filled(0, 0, 4000, 4000, Color(1, 1, 1, 200));
	draw::backdrop();


	auto outline = [&](int offset, Color color)
	{
		rect_t m_pos = rect_t(
			area.x - 75, area.y, area.w + 75, area.h
		);
		auto box = [](int x, int y, int w, int h, Color c)
		{
			render::get().line(x, y, x, y + h, c);
			render::get().line(x, y + h, x + w + 1, y + h, c);
			render::get().line(x + w, y, x + w, y + h, c);
			render::get().line(x, y, x + w, y, c);
		};
		box(m_pos.x - offset, m_pos.y - offset, m_pos.w + offset * 2, m_pos.h + offset * 2, color);
	};

	auto top_shadow = [this]() -> void {
		rect_t shadw_area = rect_t(
			area.x - 75, area.y - 20,
			area.w + 75, 20
		);

		//render::get().gradient(shadw_area.x, shadw_area.y + 20, shadw_area.w, 10, Color(26, 26, 26), Color(42, 42, 42), GRADIENT_VERTICAL);
		//render::get().gradient(shadw_area.x, shadw_area.y + 20, shadw_area.w, 10, Color(26, 26, 26), Color(31, 31, 31), GRADIENT_VERTICAL);
	};


	// lamba definitions
	/*auto top_bar = [this]() -> void {
		rect_t top_area = rect_t(
			area.x - 75,
			area.y - 7,
			area.w + 75,
			3
		);
		static float rainbow;
		rainbow += 0.0005f;
		if (rainbow > 1.f)
			rainbow = 0.f;
		auto box = [](int x, int y, int w, int h, Color c) {
			render::get().line(x, y, x, y + h, c);
			render::get().line(x, y + h, x + w + 1, y + h, c);
			render::get().line(x + w, y, x + w, y + h, c);
			render::get().line(x, y, x + w, y, c);
		};

		render::get().rect_filled(top_area.x, top_area.y, top_area.w, top_area.h, Color::Green);

		box(top_area.x - 0, top_area.y - 0, top_area.w + 0 * 2, top_area.h + 0 * 2, Color::Black);
		box(top_area.x - 1, top_area.y - 1, top_area.w + 1 * 2, top_area.h + 1 * 2, Color(48, 48, 48));
		box(top_area.x - 2, top_area.y - 2, top_area.w + 2 * 2, top_area.h + 2 * 2, Color::Black);

		auto w = render::get().text_width(fonts[HRFONT], "Hustensaft.xyz: ");
		render::get().text(fonts[HRFONT], top_area.x + 0, top_area.y + 430, Color::FromHSB(90, 1, 1), HFONT_CENTERED_Y, "Status: ");
		render::get().text(fonts[HRFONT], top_area.x + 0, top_area.y + 440, Color::Green, HFONT_CENTERED_Y, "Undetected");
		render::get().text(fonts[HRFONT], top_area.x + 0, top_area.y + 470, Color::Color::FromHSB(90, 1, 1), HFONT_CENTERED_Y, "Updated:");
		render::get().text(fonts[HRFONT], top_area.x + 0, top_area.y + 480, Color::Green, HFONT_CENTERED_Y, __DATE__);

	};*/


	rect_t main_tab_area = rect_t(
		area.x - 75, area.y,
		75, area.h
	);

	render::get().rect_filled(area.x, area.y, area.w, area.h, Color(21, 21, 21));

	render::get().rect_filled(main_tab_area.x, main_tab_area.y, main_tab_area.w, main_tab_area.h, Color(21, 21, 21));

	for (int i = 0; i < tabs.size(); i++) {
		tabs[i]->paint();
	}
	outline(0, Color::Black);
	outline(1, Color(48, 48, 48));
	outline(2, Color::Black);
	outline(3, Color(48, 48, 48));
	outline(4, Color(48, 48, 48));
	outline(5, Color(48, 48, 48));
	outline(6, Color(48, 48, 48));
	outline(7, Color(48, 48, 48));
	outline(8, Color(48, 48, 48));
	outline(9, Color(48, 48, 48));
	outline(10, Color(48, 48, 48));
	outline(11, Color(48, 48, 48));
	outline(12, Color(48, 48, 48));

	rect_t top_area = rect_t
	(
		area.x - 75,
		area.y - 1,
		area.w + 77,
		3
	);

	//render::get().gradient(top_area.x, top_area.y, 361, 3, Color(51, 132, 255, 255), Color(235, 29, 173, 255), GRADIENT_HORIZONTAL);
}

void menu::update() {
	poll_keyboard();
	int gradient[3] = {
		g_cfg.menu.menu_theme[0].r() - 20,
		g_cfg.menu.menu_theme[0].g() - 20,
		g_cfg.menu.menu_theme[0].b() - 20
	};
	for (int i = 0; i < 3; i++) {
		if (gradient[i] < 42) {
			gradient[i] = g_cfg.menu.menu_theme[0][i] + 20;
		}
	}
	g_cfg.menu.menu_theme[1] = Color(gradient[0], gradient[1], gradient[2]);
	if (key_press(g_csgo.m_inputsys()->ButtonCodeToVirtualKey(g_cfg.menu.menu_bind))) {
		toggle();
		g_csgo.m_cvar()->FindVar("cl_mouseenable")->SetValue(!active());
		g_csgo.m_inputsys()->EnableInput(!active());
		g_csgo.m_inputsys()->ResetInputState();
	}
	if (!active()) {
		return;
	}
	poll_mouse();
	render();
	rect_t main_tab_area = rect_t(
		area.x - 95, area.y, 95, area.h
	);
	for (int i = 0; i < tabs.size(); i++) {
		tabs[i]->update();
	}
	if (animating) {
		if (animate_direction == TAB_ANIMATION_DOWN) {
			if ((main_tab_area.y + animation_offset) < animation_destination) {
				animation_offset += 2;
			}
			else {
				animating = false;
			}
		}
		else {
			if ((main_tab_area.y + animation_offset) > animation_destination) {
				animation_offset -= 2;
			}
			else {
				animating = false;
			}
		}
	}
	c_mouse.paint();
}

void menu::poll_keyboard() {
	std::copy(m_keystate, m_keystate + 255, m_oldstate);
	for (auto n = 0; n < 255; ++n) {
		m_keystate[n] = GetAsyncKeyState(n);
	}
}
void menu::poll_mouse() {
	rect_t top_area = rect_t(
		area.x,
		area.y,
		area.w,
		10
	);
	if (dragging && !GetAsyncKeyState(VK_LBUTTON)) {
		dragging = false;
	}
	if (GetAsyncKeyState(VK_LBUTTON) && top_area.contains_point(c_mouse.cursor)) {
		dragging = true;
	}
	if (dragging) {
		drag_x = c_mouse.cursor.x - area.x;
		drag_y = c_mouse.cursor.y - area.y;
		GetCursorPos(&c_mouse.cursor);
		area.x = c_mouse.cursor.x - drag_x;
		area.y = c_mouse.cursor.y - drag_y;
	}
	else {
		GetCursorPos(&c_mouse.cursor);
	}
}
void menu::Mouse_t::paint() {
	render::get().rect_filled(cursor.x + 1, cursor.y, 1, 17, g_cfg.menu.menu_theme[0]);
	for (int i = 0; i < 11; i++) {
		render::get().rect_filled(cursor.x + 2 + i, cursor.y + 1 + i, 1, 1, g_cfg.menu.menu_theme[0]);
	}
	render::get().rect_filled(cursor.x + 8, cursor.y + 12, 5, 1, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 8, cursor.y + 13, 1, 1, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 9, cursor.y + 14, 1, 2, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 10, cursor.y + 16, 1, 2, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 8, cursor.y + 18, 2, 1, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 7, cursor.y + 16, 1, 2, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 6, cursor.y + 14, 1, 2, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 5, cursor.y + 13, 1, 1, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 4, cursor.y + 14, 1, 1, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 3, cursor.y + 15, 1, 1, g_cfg.menu.menu_theme[0]);
	render::get().rect_filled(cursor.x + 2, cursor.y + 16, 1, 1, g_cfg.menu.menu_theme[0]);
	for (int i = 0; i < 4; i++) {
		render::get().rect_filled(cursor.x + 2 + i, cursor.y + 2 + i, 1, 14 - (i * 2), Color::Grey);
	}
	render::get().rect_filled(cursor.x + 6, cursor.y + 6, 1, 8, Color::Grey);
	render::get().rect_filled(cursor.x + 7, cursor.y + 7, 1, 9, Color::Grey);
	for (int i = 0; i < 4; i++) {
		render::get().rect_filled(cursor.x + 8 + i, cursor.y + 8 + i, 1, 4 - i, Color::Grey);
	}
	render::get().rect_filled(cursor.x + 8, cursor.y + 14, 1, 4, Color::Grey);
	render::get().rect_filled(cursor.x + 9, cursor.y + 16, 1, 2, Color::Grey);
}