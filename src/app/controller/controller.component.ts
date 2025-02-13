import { Component } from '@angular/core';
import { FormControl, FormGroup, ReactiveFormsModule } from '@angular/forms';
import { WebSocketService } from '../services/websocket.service';
import { MatSlideToggleModule } from '@angular/material/slide-toggle';
import { MatInputModule } from '@angular/material/input';
import { MatSliderModule } from '@angular/material/slider';
import { MatCardModule } from '@angular/material/card';
import { FormsModule } from '@angular/forms';


@Component({
  selector: 'app-controller',
  standalone: true,
  imports: [ReactiveFormsModule, FormsModule, MatSlideToggleModule, MatInputModule, MatSliderModule, MatCardModule],
  providers: [],
  templateUrl: './controller.component.html',
  styleUrls: ['./controller.component.css']
})
export class ControllerComponent {
  controlForm = new FormGroup({
    mode: new FormControl('automatic'),
    targetTemperature: new FormControl(90),
    angle: new FormControl(1500),
    speed: new FormControl(100)
  });

  constructor(private wsService: WebSocketService) {}

  sendControlData() {
    this.wsService.sendMessage(this.controlForm.value);
  }
}