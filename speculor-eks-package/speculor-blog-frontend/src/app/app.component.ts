import { Component, OnInit, OnDestroy } from '@angular/core';
import { PostService } from 'src/services/post.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnInit {
  posts: any = [];

  constructor(private postSvc: PostService) {
  }

  ngOnInit(): void {
    this.postSvc.getAllPosts().subscribe(res => {
      this.posts = res;
    });
  }
}
