/*
 * SSD1306.h
 *
 * Created: 2025-01-22 21:31:53
 *  Author: Saulius
 */ 


#ifndef SSD1306_H_
#define SSD1306_H_

#define SSD1306_ADD 0x3c
#define SSD1306_CMD_COUNT 26
#define SSD1306_SCREEN_WIDTH 12    // Ekrano plotis pikseliais
#define SSD1306_SCREEN_HEIGHT 64    // Ekrano aukðtis pikseliais (64 pikseliai = 8 puslapiø)
#define SSD1306_PAGE_COUNT (SSD1306_SCREEN_HEIGHT / 8) // Puslapiø skaièius

/** @brief Maximum text length that can be displayed on the screen. */
#define MAX_TEXT_LENGTH 50

/** 
 * @brief Enumeration for text alignment options. 
 * Defines how text should be aligned on the screen: left, center, or right.
 */
typedef enum {
    ALIGN_LEFT,   /**< Left alignment. */
    ALIGN_CENTER, /**< Center alignment. */
    ALIGN_RIGHT  /**< Right alignment. */
} alignment_t;

#endif /* SSD1306_H_ */